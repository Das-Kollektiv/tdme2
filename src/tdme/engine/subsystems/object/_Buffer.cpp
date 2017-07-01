// Generated from /tdme/src/tdme/engine/subsystems/object/_Buffer.java
#include <tdme/engine/subsystems/object/_Buffer.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/nio/ByteBuffer.h>
#include <java/nio/ByteOrder.h>
#include <tdme/utils/_Console.h>

using tdme::engine::subsystems::object::_Buffer;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::nio::ByteBuffer;
using java::nio::ByteOrder;
using tdme::utils::_Console;

_Buffer::_Buffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

_Buffer::_Buffer()
	: _Buffer(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

ByteBuffer* _Buffer::byteBuffer;

ByteBuffer* _Buffer::getByteBuffer(int32_t bytes)
{
	clinit();
	if (byteBuffer == nullptr || bytes > byteBuffer->capacity()) {
		if (byteBuffer != nullptr) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Buffer::getByteBuffer(): enlarge buffer from "_j)->append(byteBuffer->capacity())
				->append(u" to "_j)
				->append(bytes)
				->append(u" bytes"_j)->toString()));
		}
		byteBuffer = ByteBuffer::allocateDirect(bytes);
	} else {
		byteBuffer->clear();
	}
	return byteBuffer;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* _Buffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.subsystems.object._Buffer", 37);
    return c;
}

void _Buffer::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		byteBuffer = ByteBuffer::allocateDirect(1024 * 1024);
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* _Buffer::getClass0()
{
	return class_();
}

