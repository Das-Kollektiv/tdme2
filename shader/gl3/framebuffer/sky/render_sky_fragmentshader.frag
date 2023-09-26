#version 330 core

precision lowp float;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

//
#define UV	vsFragTextureUV
#define COLOR	outColor

// see: https://github.com/Lexpartizan/Godot_4_sky_shader
// USING Non physical based atmospheric scattering made by robobo1221 https://www.shadertoy.com/view/Ml2cWG
uniform float TIME;
uniform sampler2D MOON;
uniform sampler2D cloud_env_texture;

uniform vec3 SUN_POS; // normalize this vector in script!
uniform vec3 MOON_POS; // normalize this vector in script
uniform vec3 MOON_TEX_POS; // normalize this vector in script!!
uniform float MOON_PHASE; // :hint_range(-1.0,1.0);
uniform float moon_radius; // :hint_range(0.0,0.5);
uniform float sun_radius; // :hint_range(0.0,0.3);
uniform float attenuation; // :hint_range(0.0,1.0);

uniform float sky_tone; // :hint_range(0.0,10.0);
uniform float sky_density; // :hint_range(0.0,2.0);
uniform float sky_rayleig_coeff; // :hint_range(0.0,10.0);
uniform float sky_mie_coeff; // :hint_range(0.0,10.0);

uniform float multiScatterPhase; // : hint_range(0.0,2.0);
uniform float anisotropicIntensity; // : hint_range(-2.0,2.0);

uniform vec4 color_sky; // : hint_color;
uniform vec4 moon_tint; // : hint_color;
uniform vec4 clouds_tint; // : hint_color;

vec3 rotate_y(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		vec3(+ca, +.0, -sa),
		vec3(+.0,+1.0, +.0),
		vec3(+sa, +.0, +ca));
}

vec3 rotate_x(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		vec3(+1.0, +.0, +.0),
		vec3(+.0, +ca, -sa),
		vec3(+.0, +sa, +ca));
}
float rand(vec2 co) {return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);}//just random function. Used for stars.

vec2 uv_sphere(vec3 rd, vec3 pos, float scale) //someone else's code, there are problems with the movement of the moon on y-axis
{
	vec3 ord = normalize(rd + 2.0*cross(pos, cross(pos, rd)));
	
	vec2 uv =vec2(atan(ord.x,ord.y),acos(ord.z));
	if (uv.x<0.0) uv.x+=3.1415926536*2.0;
	uv /= vec2(3.1415926536*2.0, 3.1415926536);
	
	uv=(uv-0.5)/scale+0.5;
	uv.x*=2.0;uv.x-=0.5;
	return uv;
}

float draw_moon(vec3 rd) 
{
	vec2 uv=uv_sphere(rd,MOON_TEX_POS,moon_radius);
    float alpha =smoothstep(moon_radius*1.44,moon_radius*1.0,length(MOON_POS-rd));
    return texture(MOON,uv).r*alpha;//+min(pow(max(dot(rd, MOON_POS), 0.0), 500.0/moon_radius) * 100.0, 1.0);
}


vec3 draw_night_sky (float sky_amount, vec3 rd, float cld_alpha, float time)
{
	vec3 night_sky = vec3(0.0);
	float moon_amount = draw_moon(rd);
	if (sky_amount<0.01 && cld_alpha == 0.0 && moon_amount < 0.01)//If the light from the Sun does not obscure the stars at sunrise/sunset and does not cover the clouds and moon
		if (rand(rd.zx) - rd.y*0.0033> 0.996) //the higher the stars, the fewer they are. Since the spherical panorama does not allow uniform coverage, the pixel density at height is higher.
			{
			float stars = rand(rd.zy)*0.5;
			stars = clamp(sin(time*3.0+stars*10.0),0.1,stars);
			night_sky.rgb = vec3(stars);
			}
	moon_amount*=1.0 - attenuation; //attenuation of the brightness of the moon (for sunrise and sunset).
	moon_amount = clamp(mix (0.0,moon_amount,smoothstep(0.9,1.0,(1.0-moon_radius)*0.5+length(MOON_POS-rd+MOON_PHASE)*(1.0-moon_radius*0.75))),0.001,1.0);//here we cast a shadow on the moon. moon phase. 
	night_sky += moon_tint.rgb*moon_amount*(clamp(1.0-cld_alpha-0.2,0.0,1.0));//Here we mix with the clouds so that there is no black border. But so that the Moon does not Shine through the clouds.
	return night_sky;
}

vec3 getSkyAbsorption(vec3 color, float h){return exp2(color * -h) * 2.0;}
float horizon_limiter (float h){return clamp(abs(h),0.1+smoothstep(0.0,0.3,SUN_POS.y)*0.2,1.0);}// eliminate the dark line and other artefacts on the horizon with clamp
float zenithDensity(float dens){return sky_density/pow(max(dens, 0.0), 0.75);}
float getSunPoint(vec3 p, vec3 lp) {return min(pow(max(dot(p,lp), 0.0), 100.0/sun_radius) * 100.0, 2.0);}//return smoothstep(sun_radius, sun_radius*0.5, distance(p, lp)) * 10.0;
float getRayleigMultiplier(vec3 p, vec3 lp){return sky_rayleig_coeff + pow(1.0 - clamp(distance(p, lp), 0.0, 1.0), 2.0) * 3.14159265359 * 0.5;}
float getMie(vec3 p, vec3 lp) { float disk = clamp(1.0 - pow(distance(p, lp), 0.1), 0.0, 1.0); return disk*disk*(3.0 - 2.0 * disk) * sky_mie_coeff * 3.14159265359;}
vec3 jodieReinhardTonemap(vec3 color){ vec3 tc = color / (color + 1.0); return mix(color / (dot(color, vec3(0.2126, 0.7152, 0.0722)) + 1.0), tc, tc);}

vec3 getAtmosphericScattering(vec3 p, vec3 lp){
	vec3 skyColor = color_sky.rgb * (1.0 + anisotropicIntensity);
	float zenith = zenithDensity(horizon_limiter(p.y));
	float sunPointDistMult =  clamp(max(lp.y + multiScatterPhase, 0.0), 0.0, 1.0);
	vec3 absorption = getSkyAbsorption(skyColor, zenith);
    vec3 sunAbsorption = getSkyAbsorption(skyColor, zenithDensity(lp.y + multiScatterPhase));
	vec3 sky = skyColor * zenith *getRayleigMultiplier(p, lp);
	sky = mix(sky * absorption, sky / (sky + 0.5), sunPointDistMult) + getSunPoint(p, lp) * absorption + getMie(p, lp) * sunAbsorption;
	sky *= sunAbsorption * 0.5 + 0.5 * length(sunAbsorption);
	sky = jodieReinhardTonemap(sky);
	sky = pow(sky, vec3(sky_tone));
	return sky;
}

void main(void){
	vec2 uv = vsFragTextureUV;
    uv.x = 2.0 * uv.x - 1.0;
    uv.y = 2.0 * uv.y - 1.0;
	vec3 rd = normalize(rotate_y(rotate_x(vec3(0.0, 0.0, 1.0),-uv.y*3.1415926535/2.0),-uv.x*3.1415926535)); //transform UV to spherical panorama 3d coords
	rd.x*=-1.0; ////The x-axis is inverted on the godot scene for unknown reasons

	vec4 cld = texture(cloud_env_texture, 1.0 - UV); // The axis is inverted on the godot scene for unknown reasons,so gor godrays inverted them!
	cld.rgb *=attenuation; // lighten the clouds depending on the height of the Sun, calculated in the script
	cld*=clouds_tint;
	vec3 sky;
	sky = getAtmosphericScattering(rd,SUN_POS);
	sky += draw_night_sky(max(max(sky.b,sky.r),sky.g),rd,cld.a,TIME);
	sky = mix(sky, cld.rgb/(0.0001+cld.a), cld.a);
	COLOR=vec4(sky,1.0);

}
