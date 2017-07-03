// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/nio/Buffer.h>
#include <Array.h>

using java::nio::Buffer;
extern void unimplemented_(const char16_t* name);

java::nio::Buffer::Buffer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::nio::Buffer::Buffer(int32_t capacity)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(capacity);
}

java::nio::Buffer::Buffer(Buffer* buffer)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
	ctor(buffer);
}

java::nio::Buffer::Buffer(int32_t capacity, int8_t* data) {
	clinit();
	ctor(capacity, data);
}

void Buffer::ctor(int32_t capacity) {
	capacity_ = capacity;
	buffer = new int8_t[capacity];
}

void Buffer::ctor(Buffer* buffer) {
	this->capacity_ = buffer->capacity_;
	this->buffer = buffer->buffer;
}

void Buffer::ctor(int32_t capacity, int8_t* data) {
	this->capacity_ = capacity;
	this->buffer = data;
}

int32_t Buffer::capacity()
{ /* stub */
	return capacity_;
}

Buffer* Buffer::clear()
{ /* stub */
	position_ = 0;
	return this;
}

bool Buffer::hasRemaining()
{ /* stub */
	return position_ < capacity_;
}

int32_t Buffer::position() {
	return position_;
}

int32_t Buffer::limit() {
	return position_;
}

int8_t Buffer::get(int32_t position) {
	return buffer[position];
}

Buffer* Buffer::put(int8_t arg0) {
	buffer[position_++] = arg0;
}

Buffer* Buffer::put(int8_tArray* arg0) {
	for (int i = 0; i < arg0->length; i++) {
		put(arg0->get(i));
	}
}

const int8_t* Buffer::getBuffer() {
	return buffer;
}

int32_t Buffer::remaining()
{ /* stub */
	return capacity_ - position_;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Buffer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.nio.Buffer", 15);
    return c;
}

java::lang::Class* Buffer::getClass0()
{
	return class_();
}

