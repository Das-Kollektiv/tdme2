// Generated from /tdme/src/tdme/engine/FrameBuffer.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Object.h>

struct default_init_tag;

/** 
 * Application
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::Application
{
public:

	/**
	 * Public constructor
	 */
	Application();

	/**
	 * Destructor
	 */
	virtual ~Application();

	/**
	 * Run this application
	 * @param argument count
	 * @param argument values
	 * @param title
	 */
	void run(int argc, char** argv, const char *title);

	/** 
	 * Init
	 */
	virtual void initialize() = 0;

	/** 
	 * Resize
	 * @param width
	 * @param height
	 */
	virtual void reshape(int32_t width, int32_t height) = 0;

	/** 
	 * Display
	 */
	virtual void display() = 0;

	/**
	 * Disposes this frame buffer
	 */
	virtual void dispose() = 0;

private:
	static Application* application;
	bool initialized { false };

	/**
	 * GLUT display function
	 */
	static void glutDisplay();

	/**
	 * GLUT reshape function
	 */
	static void glutReshape(int32_t width, int32_t height);

};
