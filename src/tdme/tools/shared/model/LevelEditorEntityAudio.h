#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Level editor entity audio
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::model::LevelEditorEntityAudio
{
private:
	LevelEditorEntity* entity;
	string animation { "" };
	string fileName { "" };
	float gain { 1.0f };
	float pitch { 1.0f };
	int offset { 0 };
	bool looping { false };
	bool fixed { false };

public:

	/**
	 * Public constructor
	 * @param levelEditorEntity level editor entity
	 */
	inline LevelEditorEntityAudio(LevelEditorEntity* entity, const string& animation): entity(entity), animation(animation) {
	}

	/**
	 * Destructor
	 */
	~LevelEditorEntityAudio();

	/**
	 * @return entity
	 */
	inline LevelEditorEntity* getEntity() {
		return entity;
	}

	/**
	 * @return animation
	 */
	inline const string& getAnimation() {
		return animation;
	}

	/**
	 * @return file name
	 */
	inline const string& getFileName() const {
		return fileName;
	}

	/**
	 * Set file name
	 * @param fileName file name
	 */
	inline void setFileName(const string& fileName) {
		this->fileName = fileName;
	}

	/**
	 * @return gain
	 */
	inline float getGain() const {
		return gain;
	}

	/**
	 * Set gain
	 * @param gain gain
	 */
	inline void setGain(float gain) {
		this->gain = gain;
	}

	/**
	 * @return pitch
	 */
	inline float getPitch() const {
		return pitch;
	}

	/**
	 * Set pitch
	 * @param pitch pitch
	 */
	inline void setPitch(float pitch) {
		this->pitch = pitch;
	}

	/**
	 * @return offset in ms
	 */
	inline int getOffset() const {
		return offset;
	}

	/**
	 * Set offset in ms
	 * @param offset offset
	 */
	inline void setOffset(int offset) {
		this->offset = offset;
	}

	/**
	 * @return is looping
	 */
	inline bool isLooping() const {
		return looping;
	}

	/**
	 * Set looping
	 * @param looping looping
	 */
	inline void setLooping(bool looping) {
		this->looping = looping;
	}

	/**
	 * @return fixed
	 */
	inline bool isFixed() const {
		return fixed;
	}

	/**
	 * Set fixed
	 * @param fixed fixed
	 */
	inline void setFixed(bool fixed) {
		this->fixed = fixed;
	}

};
