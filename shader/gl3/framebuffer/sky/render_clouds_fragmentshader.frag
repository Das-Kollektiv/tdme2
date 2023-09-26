#version 330 core

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

// see: https://github.com/Lexpartizan/Godot_4_sky_shader
// USING https://www.shadertoy.com/view/XtBXDw for 3dclouds and https://www.shadertoy.com/view/4dsXWn for 2d clouds
uniform float TIME;
uniform vec3 WIND; //wind_vec*wind_str направление ветра, вектор*силу ветра
uniform sampler2D Noise;

uniform vec3 SUN_POS; //normalize this vector in script!

uniform float SIZE; // :hint_range(0.0,10.0); //0.5
uniform float SOFTNESS; // :hint_range(0.0,10.0); //0.5
uniform float COVERAGE; // :hint_range(0.0,1.0); //0.5
uniform float HEIGHT; // :hint_range(0.0,1.0); //0.0
uniform float THICKNESS; // :hint_range(0.0,100.0); //25.
uniform float ABSORPTION; // :hint_range(0.0,10.0); //1.030725
uniform int STEPS; // :hint_range(0,100); //25

vec3 rotate_y(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		vec3(+ca, +.0, -sa),
		vec3(+.0,+1.0, +.0),
		vec3(+sa, +.0, +ca));
}

vec3 rotate_x(vec3 v,float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		vec3(+1.0, +.0, +.0),
		vec3(+.0, +ca, -sa),
		vec3(+.0, +sa, +ca));
}

float rand(vec2 co) {return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);}//просто пример рандома в шейдерах из инета

float noise( in vec3 pos )
{
    pos*=0.01;
	float  z = pos.z*256.0;
	vec2 offz = vec2(0.317,0.123);
	vec2 uv = pos.xy + offz*floor(z);
	return mix(textureLod( Noise, uv ,0.0).x,textureLod( Noise, uv+offz ,0.0).x,fract(z));
}

float get_noise(vec3 p, float FBM_FREQ)
{
	float
	t  = 0.51749673 * noise(p); p *= FBM_FREQ;
	t += 0.25584929 * noise(p); p *= FBM_FREQ;
	t += 0.12527603 * noise(p); p *= FBM_FREQ;
	t += 0.06255931 * noise(p);
	return t;
}

bool SphereIntersect(vec3 apos, float arad, vec3 ro, vec3 rd, out vec3 norm)
{
    ro -= apos;
    float A = dot(rd, rd);
    float B = 2.0*dot(ro, rd);
    float C = dot(ro, ro)-arad*arad;
    float D = B*B-4.0*A*C;
    if (D < 0.0) return false;
    D = sqrt(D);
    A *= 2.0;
    float t1 = (-B+D)/A;
    float t2 = (-B-D)/A;
    if (t1 < 0.0) t1 = t2;
    if (t2 < 0.0) t2 = t1;
    t1 = min(t1, t2);
    if (t1 < 0.0) return false;
    norm = ro+t1*rd;
    return true;
}

float density(vec3 pos, vec3 offset)
{
	vec3 p = pos * 0.02/SIZE + offset;
	float dens = get_noise(p,2.0+SOFTNESS);
	dens *= smoothstep (COVERAGE, COVERAGE + .07, dens);
	return clamp(dens, 0.0, 1.0);	
}

vec4 clouds_3d(vec3 ro, vec3 rd, vec3 wind)
{
	vec3 apos=vec3(0, -450, 0);
	float arad=500.0;
    vec3 C = vec3(0, 0, 0);
	float alpha = 0.0;
    vec3 norm;
    if(SphereIntersect(apos,arad,ro,rd,norm)){
        int steps = STEPS;
        float march_step = THICKNESS / float(steps);
        vec3 dir_step = rd / rd.y * march_step;
        vec3 pos =norm;
        float T = 1.0;
        for (int i = 0; i < steps; i++) {
            if (length(pos) > 1e3) break;
			float dens = density (pos, wind)*march_step;
			float T_i = exp(-ABSORPTION * dens);
            T *= T_i;
            if (T < .01) break;
			float h = float(i) / float(steps);
            C += T * (exp(h)/2.0 ) *dens;
            alpha += (1. - T_i) * (1. - alpha);
            pos += dir_step;
			}
		}
		return vec4(C, alpha);
}

vec3 cube_bot(vec3 p, vec3 c1, vec3 c2, float time)
{
	float f = 0.0;
	f += .50000 * noise(.5 * (p+vec3(0.,0.,-time*0.275)));
	f += .25000 * noise(1. * (p+vec3(0.,0.,-time*0.275)));
	f += .12500 * noise(2. * (p+vec3(0.,0.,-time*0.275)));
	f += .06250 * noise(4. * (p+vec3(0.,0.,-time*0.275)));
	return  f* mix(c1, c2, p * .5 + .5);
}

float MapSH(vec3 p, float cloudy,vec3 offset, float CLOUD_UPPER)
{
	float h = -(get_noise(p*0.0003+offset, 2.76434)-cloudy-.6);
    h *= smoothstep((HEIGHT+0.1)*CLOUD_UPPER+100., (HEIGHT+0.1)*CLOUD_UPPER, p.y);
	return h;
}

vec4 clouds_2d(vec3 rd, vec3 wind)
{
	float CLOUD_LOWER=7000.0;
	float CLOUD_UPPER=9000.0;
	float cloudy = (1.0-COVERAGE)-0.5;
	float beg = (((HEIGHT+0.1)*CLOUD_LOWER) / rd.y);
	float end = (((HEIGHT+0.1)*CLOUD_UPPER) / rd.y);
	vec3 p = vec3(rd * beg);
	vec3 add = rd * ((end-beg) / 55.0);
	vec2 shade;
	vec2 shadeSum = vec2(0.0, 0.0);
	for (int i = 0; i < min(STEPS,5); i++)
	{
		if (shadeSum.y >= 1.0) break;
		float h = MapSH(p,cloudy,wind,CLOUD_UPPER);
		shade.y = max(h, 0.0);
        shade.x = clamp(-(h-MapSH(p+SUN_POS*200.0, cloudy,wind,CLOUD_UPPER))*2., 0.05, 1.0);
		shadeSum += shade * (1.0 - shadeSum.y);
		p += add;
	}
	vec3 clouds = mix(vec3(pow(shadeSum.x, .6)), vec3(1.0), (1.0-shadeSum.y)*.4);
    clouds = clamp(mix(vec3(0.0), min(clouds, 1.0), shadeSum.y),0.0,1.0);
	return vec4(clouds, shadeSum.y);
}

void main(void){
	vec2 uv = vsFragTextureUV;
	uv.x = 2.0 * uv.x - 1.0;
	uv.y = 2.0 * uv.y - 1.0;
	vec3 rd = normalize(rotate_y(rotate_x(vec3(0.0, 0.0, 1.0),-uv.y*3.1415926535/2.0),-uv.x*3.1415926535)); //transform UV to spherical panorama 3d coords
	//rd.x*=-1.0; //The x-axis is inverted on the godot scene for unknown reasons
	vec3 ro = vec3(0.0, -200.0*HEIGHT+40.0, 0.0); //This is the vector of displacement of the sphere relative to zero coordinates. Here you can set the height of the clouds. That is, to make a sphere with clouds higher or lower.
	vec4 cld = vec4(0.0);
	float skyPow = dot(rd, vec3(0.0, -1.0, 0.0));
	float horizonPow =1.-pow(1.0-abs(skyPow), 5.0);
	if(rd.y>0.0)
	{
		if (STEPS < 20) cld = clouds_2d(rd,WIND*TIME); else cld=clouds_3d(ro,rd,WIND*TIME/SIZE);
		cld=clamp(cld,0.0,1.0);
		cld.rgb+=0.04*cld.rgb*horizonPow;
		cld*=clamp((  1.0 - exp(-2.3 * pow(max((0.0), horizonPow), (2.6)))),0.,1.);//Here we dissolve the clouds in the horizon for a smooth transition to the horizon line.
	}
	else
	{
		cld.rgb = cube_bot(rd,vec3(1.5,1.49,1.71), vec3(1.1,1.15,1.5),TIME);
		cld.a=1.;
		cld*=clamp((  1.0 - exp(-1.3 * pow(max((0.0), horizonPow), (2.6)))),0.,1.);
	}
	outColor = vec4(cld.rgb/(0.0001+cld.a) * 100.0, 1.0f);
}
