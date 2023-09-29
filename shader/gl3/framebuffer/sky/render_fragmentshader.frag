#version 330 core

precision lowp float;

// passed from vertex shader
in vec2 vsFragTextureUV;

// passed out
out vec4 outColor;

#define PI  3.14159265359
#define PI2 6.28318530718

#define UV	vsFragTextureUV

//
uniform int LIGHT0_ENABLED;
uniform vec3 LIGHT0_DIRECTION;
uniform int LIGHT1_ENABLED;
uniform vec3 LIGHT1_DIRECTION;
uniform sampler2D stars_texture;

uniform float time;
uniform float aspectRatio;
uniform vec3 sideVector;
uniform vec3 upVector;
uniform vec3 forwardVector;

vec3 EYEDIR;

// see: https://godotshaders.com/shader/stylized-sky-with-procedural-sun-and-moon/
// sky
const vec3 day_top_color = vec3( 0.1, 0.6, 1.0 );
const vec3 day_bottom_color = vec3( 0.4, 0.8, 1.0 );
const vec3 sunset_top_color = vec3( 0.7, 0.75, 1.0 );
const vec3 sunset_bottom_color = vec3( 1.0, 0.5, 0.7 );
const vec3 night_top_color = vec3( 0.02, 0.0, 0.04 );
const vec3 night_bottom_color = vec3( 0.1, 0.0, 0.2 );
// horizon
const vec3 horizon_color = vec3( 0.0, 0.7, 0.8 );
const float horizon_blur = 0.05;
// sun
const float sun_color_factor = 200.0;
const vec3 sun_color = vec3( 1.0, 0.8, 0.1 );
const vec3 sun_sunset_color = vec3( 10.0, 0.0, 0.0 );
const float sun_size = 0.2;
const float sun_blur = 10.0;
// moon
const float moon_color_factor = 20.0;
const vec3 moon_color = vec3( 1.0, 0.95, 0.7 );
const float moon_size = 0.06;
const float moon_blur = 0.1;
// clouds
const vec3 clouds_edge_color = vec3( 0.8, 0.8, 0.98 );
const vec3 clouds_top_color = vec3( 1.0, 1.0, 1.00 );
const vec3 clouds_middle_color = vec3( 0.92, 0.92, 0.98 );
const vec3 clouds_bottom_color = vec3( 0.83, 0.83, 0.94 );
const float clouds_speed = 2.0;
const float clouds_direction = 0.2;
const float clouds_scale = 1.0;
const float clouds_cutoff = 0.3;
const float clouds_fuzziness = 0.5;
const float clouds_weight = 0.0;
const float clouds_blur = 0.25;
const float stars_speed = 1.0;

// Originaly based on https://godotshaders.com/shader/stylized-sky-shader-with-clouds/ but there's not much left

/*
// group_uniforms sky;
	uniform vec3 day_top_color : source_color = vec3( 0.1, 0.6, 1.0 );
	uniform vec3 day_bottom_color : source_color = vec3( 0.4, 0.8, 1.0 );
	uniform vec3 sunset_top_color : source_color = vec3( 0.7, 0.75, 1.0 );
	uniform vec3 sunset_bottom_color : source_color = vec3( 1.0, 0.5, 0.7 );
	uniform vec3 night_top_color : source_color = vec3( 0.02, 0.0, 0.04 );
	uniform vec3 night_bottom_color : source_color = vec3( 0.1, 0.0, 0.2 );

// group_uniforms horizon;
	uniform vec3 horizon_color : source_color = vec3( 0.0, 0.7, 0.8 );
	uniform float horizon_blur : hint_range( 0.0, 1.0, 0.01 ) = 0.05;

// group_uniforms sun; // First DirectionalLight3D will be the sun
	uniform vec3 sun_color : source_color = vec3( 10.0, 8.0, 1.0 );
	uniform vec3 sun_sunset_color : source_color = vec3( 10.0, 0.0, 0.0 );
	uniform float sun_size : hint_range( 0.01, 1.0 ) = 0.2;
	uniform float sun_blur : hint_range( 0.01, 20.0 ) = 10.0;

// group_uniforms moon; // Second DirectionalLight3D will be the moon
	uniform vec3 moon_color : source_color = vec3( 1.0, 0.95, 0.7 );
	uniform float moon_size : hint_range( 0.01, 1.0 ) = 0.06;
	uniform float moon_blur : hint_range( 0.01, 10.0 ) = 0.1;

// group_uniforms clouds;
	// Replaced by noise functions, unncomment if you want to use graphical textures
//	uniform sampler2D clouds_top_texture : filter_linear_mipmap, hint_default_black;
//	uniform sampler2D clouds_middle_texture : filter_linear_mipmap, hint_default_black;
//	uniform sampler2D clouds_bottom_texture : filter_linear_mipmap, hint_default_black;
	uniform vec3 clouds_edge_color : source_color = vec3( 0.8, 0.8, 0.98 );
	uniform vec3 clouds_top_color : source_color = vec3( 1.0, 1.0, 1.00 );
	uniform vec3 clouds_middle_color : source_color = vec3( 0.92, 0.92, 0.98 );
	uniform vec3 clouds_bottom_color : source_color = vec3( 0.83, 0.83, 0.94 );
	uniform float clouds_speed : hint_range( 0.0, 20.0, 0.01 ) = 2.0;
	uniform float clouds_direction : hint_range( -0.5, 0.5, 0.0 ) = 0.2;
	uniform float clouds_scale : hint_range( 0.0, 4.0, 0.01 ) = 1.0;
	uniform float clouds_cutoff : hint_range( 0.0, 1.0, 0.01 ) = 0.3;
	uniform float clouds_fuzziness : hint_range( 0.0, 2.0, 0.01 ) = 0.5;
	// More weight is simply a darker color, usefull for rain/storm
	uniform float clouds_weight : hint_range( 0.0, 1.0, 0.01 ) = 0.0;
	uniform float clouds_blur : hint_range( 0.0, 1.0, 0.01 ) = 0.25;

// group_uniforms stars;
	// Stars should be at black background
	uniform sampler2D stars_texture : filter_linear_mipmap, hint_default_black;
	uniform float stars_speed : hint_range( 0.0, 20.0, 0.01 ) = 1.0;
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
	// Function for clouds noises. You can replace using "gen_fractal_ping_pong" with a simple texture reading.
	// I was frustrated with the repeating texture that's why I included the algorithm in the code.
	// Source: https://github.com/Auburn/FastNoiseLite/tree/master
	const int PRIME_X = 501125321;
	const int PRIME_Y = 1136930381;
	float lerp( float a, float b, float t )
	{
		return a + t * ( b - a );
	}
	float cubic_lerp( float a, float b, float c, float d, float t )
	{
		float p = d - c - ( a - b );
		return t * t * t * p + t * t * ( a - b - p ) + t * ( c - a ) + b;
	}
	float ping_pong( float t )
	{
		t -= trunc( t * 0.5 ) * 2.0;
		return t < 1.0 ? t : 2.0 - t;
	}
	int hash( int seed, int x_primed, int y_primed )
	{
		return ( seed ^ x_primed ^ y_primed ) * 0x27d4eb2d;
	}
	float val_coord( int seed, int x_primed, int y_primed )
	{
	    int hash = hash( seed, x_primed, y_primed );
	    hash *= hash;
	    hash ^= hash << 19;
	    return float( hash ) * ( 1.0 / 2147483648.0 );
	}
	float single_value_cubic( int seed, float x, float y )
	{
	    int x1 = int( floor( x ));
	    int y1 = int( floor( y ));

	    float xs = x - float( x1 );
	    float ys = y - float( y1 );

	    x1 *= PRIME_X;
	    y1 *= PRIME_Y;
	    int x0 = x1 - PRIME_X;
	    int y0 = y1 - PRIME_Y;
	    int x2 = x1 + PRIME_X;
	    int y2 = y1 + PRIME_Y;
	    int x3 = x1 + ( PRIME_X << 1 );
	    int y3 = y1 + ( PRIME_Y << 1 );

	    return cubic_lerp(
	        cubic_lerp( val_coord( seed, x0, y0 ), val_coord( seed, x1, y0 ), val_coord( seed, x2, y0 ), val_coord( seed, x3, y0 ), xs ),
	        cubic_lerp( val_coord( seed, x0, y1 ), val_coord( seed, x1, y1 ), val_coord( seed, x2, y1 ), val_coord( seed, x3, y1 ), xs ),
	        cubic_lerp( val_coord( seed, x0, y2 ), val_coord( seed, x1, y2 ), val_coord( seed, x2, y2 ), val_coord( seed, x3, y2 ), xs ),
	        cubic_lerp( val_coord( seed, x0, y3 ), val_coord( seed, x1, y3 ), val_coord( seed, x2, y3 ), val_coord( seed, x3, y3 ), xs ),
	    ys ) * ( 1.0 / ( 1.5 * 1.5 ));
	}
	// Params can be change in the same way as in noise settings in Godot
	const float FRACTAL_BOUNDING = 1.0 / 1.75;
	const int OCTAVES = 5;
	const float PING_PONG_STRENGTH = 2.0;
	const float WEIGHTED_STRENGTH = 0.0;
	const float GAIN = 0.5;
	const float LACUNARITY = 2.0;
	float gen_fractal_ping_pong( vec2 pos, int seed, float frequency )
	{
		float x = pos.x * frequency;
		float y = pos.y * frequency;
	    float sum = 0.0;
		float amp = FRACTAL_BOUNDING;
	    for( int i = 0; i < OCTAVES; i++ )
	    {
	        float noise = ping_pong(( single_value_cubic( seed++, x, y ) + 1.0 ) * PING_PONG_STRENGTH );
	        sum += ( noise - 0.5 ) * 2.0 * amp;
	        amp *= lerp( 1.0, noise, WEIGHTED_STRENGTH );
	        x *= LACUNARITY;
	        y *= LACUNARITY;
	        amp *= GAIN;
	    }
	    return sum * 0.5 + 0.5;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////

// Function needed to calculate the phase of the moon
// Source: https://kelvinvanhoorn.com/2022/03/17/skybox-tutorial-part-1/
float sphere_intersect( vec3 view_dir, vec3 sphere_pos, float radius )
{
    float b = dot( -sphere_pos, view_dir );
    float c = dot( -sphere_pos, -sphere_pos ) - pow( radius, 2 );
    float h = pow( b, 2 ) - c;
    return h < 0.0 ? -1.0 : -b - sqrt( h );
}

void main(void)
{
	// Calculate the direction vector based on camera orientation
	vec2 uv = vsFragTextureUV - 0.5;
	EYEDIR = normalize(forwardVector + uv.x * (sideVector * aspectRatio) + uv.y * upVector);
	vec3 COLOR = vec3(0.0);

	//////////////////// SKY ///////////////////////////////////////////////////////////////////////
	float _eyedir_y = abs( sin( EYEDIR.y * PI * 0.5 ));

	// The day color will be our base color
	vec3 _sky_color = mix( day_bottom_color, day_top_color, _eyedir_y );
	_sky_color = mix( _sky_color, vec3( 0.0 ), clamp(( 0.7 - clouds_cutoff ) * clouds_weight, 0.0, 1.0 ));
	float _sunset_amount = clamp( 0.5 - abs( LIGHT0_DIRECTION.y ), 0.0, 0.5 ) * 2.0;
	// The sky should be more red around the west, on the opposite side you don't see it as much
	float _sunset_distance = clamp( 1.0 - pow( distance( EYEDIR, LIGHT0_DIRECTION ), 2 ), 0.0, 1.0 );
	vec3 _sky_sunset_color = mix( sunset_bottom_color, sunset_top_color, _eyedir_y + 0.5 );
	_sky_sunset_color = mix( _sky_sunset_color, sunset_bottom_color, _sunset_amount * _sunset_distance );
	_sky_color = mix( _sky_color, _sky_sunset_color, _sunset_amount );

	float _night_amount = clamp( -LIGHT0_DIRECTION.y + 0.7, 0.0, 1.0 );
	vec3 _sky_night_color = mix( night_bottom_color, night_top_color, _eyedir_y );
	_sky_color = mix( _sky_color, _sky_night_color, _night_amount );

	// Final sky color
	COLOR = _sky_color;

	//////////////////// HORIZON ///////////////////////////////////////////////////////////////////
	float _horizon_amount = 0.0;
	if( EYEDIR.y < 0.0 )
	{
		_horizon_amount = clamp( abs( EYEDIR.y ) / horizon_blur, 0.0, 1.0 );
		// Mixing with the color of the night sky to make the horizon darker
		vec3 _horizon_color = mix( horizon_color, _sky_color, _night_amount * 0.9 );
		// And if ther are many dark clouds, we also make the horizon darker
		_horizon_color = mix( _horizon_color, vec3( 0.0 ), ( 1.0 - clouds_cutoff ) * clouds_weight * 0.7 );
		COLOR = mix( COLOR, _horizon_color, _horizon_amount );
	}

	//////////////////// MOON //////////////////////////////////////////////////////////////////////
	float _moon_amount = 0.0;
	if( LIGHT1_ENABLED == 1)
	{
		// Bigger moon near the horizon
		float _moon_size = moon_size + cos( LIGHT1_DIRECTION.y * PI ) * moon_size * 0.25;
		float _moon_distance = distance( EYEDIR, LIGHT1_DIRECTION ) / _moon_size;
		// Finding moon disc and edge blur
		_moon_amount = clamp(( 1.0 - _moon_distance ) / moon_blur, 0.0, 1.0 );
		if( _moon_amount > 0.0 )
		{
			// Moon illumination depending on the position of the sun
			float _moon_intersect = sphere_intersect( EYEDIR, LIGHT1_DIRECTION, _moon_size );
			vec3 _moon_normal = normalize( LIGHT1_DIRECTION - EYEDIR * _moon_intersect );
			// Power on the result gives a better effect
			float _moon_n_dot_l = pow( clamp( dot( _moon_normal, -LIGHT0_DIRECTION ), 0.05, 1.0 ), 2 );
			// Hiding the moon behind the horizon
			_moon_amount *= 1.0 - _horizon_amount;
			COLOR = mix( COLOR, moon_color * moon_color_factor, _moon_n_dot_l * _moon_amount );
		}
	}

	//////////////////// SUN ///////////////////////////////////////////////////////////////////////
	float _sun_distance = 0.0;
	if( LIGHT0_ENABLED == 1)
	{
		_sun_distance = distance( EYEDIR, LIGHT0_DIRECTION );
		// Bigger sun near the horizon
		float _sun_size = sun_size + cos( LIGHT0_DIRECTION.y * PI ) * sun_size * 0.25;
		// Finding sun disc and edge blur
		float _sun_amount = clamp(( 1.0 - _sun_distance / _sun_size ) / sun_blur, 0.0, 1.0 );
		if( _sun_amount > 0.0 )
		{
			// Changing color of the sun during sunset
			float _sunset_amount = 1.0;
			if( LIGHT0_DIRECTION.y > 0.0 )
				_sunset_amount = clamp( cos( LIGHT0_DIRECTION.y * PI ), 0.0, 1.0 );
			vec3 _sun_color = mix( sun_color * sun_color_factor, sun_sunset_color, _sunset_amount );
			// Hiding the sun behind the moon
			_sun_amount = clamp( _sun_amount * ( 1.0 - _moon_amount ), 0.0, 1.0 );
			// Hiding the sun behind the horizon
			_sun_amount *= 1.0 - _horizon_amount;
			// Leveling the "glow" in color
			/*
			// TODO: does not work, need to check (adrewke)
			if( _sun_color.r > 1.0 || _sun_color.g > 1.0 || _sun_color.b > 1.0 )
				_sun_color *= _sun_amount;
			*/
			COLOR = mix( COLOR, _sun_color, _sun_amount );
		}
	}

	//////////////////// STARS /////////////////////////////////////////////////////////////////
	vec2 _sky_uv = EYEDIR.xz / sqrt( EYEDIR.y );
	if( EYEDIR.y > -0.01 && LIGHT0_DIRECTION.y < 0.0  )
	{
		// Stars UV rotation
		float _stars_speed_cos = cos( stars_speed * time * 0.005 );
		float _stars_speed_sin = sin( stars_speed * time * 0.005 );
		vec2 _stars_uv = vec2(
			_sky_uv.x * _stars_speed_cos - _sky_uv.y * _stars_speed_sin,
			_sky_uv.x * _stars_speed_sin + _sky_uv.y * _stars_speed_cos
		);
		// Stars texture
		vec3 _stars_color = texture( stars_texture, _stars_uv ).rgb * -LIGHT0_DIRECTION.y;
		// Hiding stars behind the moon
		_stars_color *= 1.0 - _moon_amount;
		COLOR += _stars_color;
	}

	//////////////////// CLOUDS ////////////////////////////////////////////////////////////////
	if( EYEDIR.y > 0.0 )
	{
		// Clouds UV movement direction
		float _clouds_speed = time * clouds_speed * 0.01;
		float _sin_x = sin( clouds_direction * PI * 2.0 );
		float _cos_y = cos( clouds_direction * PI * 2.0 );
		// I using 3 levels of clouds. Top is the lightes and botom the darkest.
		// The speed of movement (and direction a little) is different for the illusion of the changing shape of the clouds.
		vec2 _clouds_movement = vec2( _sin_x, _cos_y ) * _clouds_speed;
//		float _noise_top = texture( clouds_top_texture, ( _sky_uv + _clouds_movement ) * clouds_scale ).r;
		float _noise_top = gen_fractal_ping_pong( ( _sky_uv + _clouds_movement ) * clouds_scale, 0, 0.5 );
		_clouds_movement = vec2( _sin_x * 0.97, _cos_y * 1.07 ) * _clouds_speed * 0.89;
//		float _noise_middle = texture( clouds_middle_texture, ( _sky_uv + _clouds_movement ) * clouds_scale ).r;
		float _noise_middle = gen_fractal_ping_pong( ( _sky_uv + _clouds_movement ) * clouds_scale, 1, 0.75 );
		_clouds_movement = vec2( _sin_x * 1.01, _cos_y * 0.89 ) * _clouds_speed * 0.79;
//		float _noise_bottom = texture( clouds_bottom_texture, ( _sky_uv + _clouds_movement ) * clouds_scale ).r;
		float _noise_bottom = gen_fractal_ping_pong( ( _sky_uv + _clouds_movement ) * clouds_scale, 2, 1.0 );
		// Smoothstep with the addition of a noise value from a lower level gives a nice, deep result
		_noise_bottom = smoothstep( clouds_cutoff, clouds_cutoff + clouds_fuzziness, _noise_bottom );
		_noise_middle = smoothstep( clouds_cutoff, clouds_cutoff + clouds_fuzziness, _noise_middle + _noise_bottom * 0.2 ) * 1.1;
		_noise_top = smoothstep( clouds_cutoff, clouds_cutoff + clouds_fuzziness, _noise_top + _noise_middle * 0.4 ) * 1.2;
		float _clouds_amount = clamp( _noise_top + _noise_middle + _noise_bottom, 0.0, 1.0 );
		// Fading clouds near the horizon
		_clouds_amount *= clamp( abs( EYEDIR.y ) / clouds_blur, 0.0, 1.0 );

		vec3 _clouds_color = mix( vec3( 0.0 ), clouds_top_color, _noise_top );
		_clouds_color = mix( _clouds_color, clouds_middle_color, _noise_middle );
		_clouds_color = mix( _clouds_color, clouds_bottom_color, _noise_bottom );
		// The edge color gives a nice smooth edge, you can try turning this off if you need sharper edges
		_clouds_color = mix( clouds_edge_color, _clouds_color, _noise_top );
		// The sun passing through the clouds effect
		_clouds_color = mix( _clouds_color, clamp( sun_color * sun_color_factor, 0.0, 1.0 ), pow( 1.0 - clamp( _sun_distance, 0.0, 1.0 ), 5 ));
		// Color combined with sunset condition
		_clouds_color = mix( _clouds_color, sunset_bottom_color, _sunset_amount * 0.75 );
		// Color depending on the "progress" of the night.
		_clouds_color = mix( _clouds_color, _sky_color, clamp( _night_amount, 0.0, 0.98 ));
		_clouds_color = mix( _clouds_color, vec3( 0.0 ), clouds_weight * 0.9 );
		COLOR = mix( COLOR, _clouds_color, _clouds_amount );
	}

	//
	outColor = vec4(COLOR, 1.0);
}
