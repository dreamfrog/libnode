// Copyright (c) 2012 Plenluno All rights reserved.

#include <string>

#include "libnode/buffer.h"

namespace libj {
namespace node {

class BufferImpl : public Buffer {
 public:
    static Ptr create(Size length) {
        Ptr p(new BufferImpl(length));
        return p;
    }

    static Ptr create(const UByte* data, Size length) {
        Ptr p(new BufferImpl(length));
        for (Size i = 0; i < length; i++)
            p->setUInt8(i, data[i]);
        return p;
    }

    static Ptr create(String::CPtr str, String::Encoding enc) {
        if (enc == String::UTF8) {
            std::string str8 = str->toStdString();
            Size length = str8.length();
            return create(
                reinterpret_cast<const UByte*>(str8.c_str()), length);
        } else {
            LIBJ_NULL_PTR(Buffer, nullp);
            return nullp;
        }
    }

    void write(
        String::CPtr str,
        Size offset = 0,
        Size length = NO_POS,
        String::Encoding enc = String::UTF8) {
        // TODO(KotaHanda): implement
    }

    virtual Value slice(Size begin, Size end) const {
        Value val = buffer_->slice(begin, end);
        JsArrayBuffer::Ptr buf = toPtr<JsArrayBuffer>(val);
        Ptr p(new BufferImpl(buf));
        return p;
    }

    virtual void copy(
        Ptr target,
        Size targetStart,
        Size sourceStart,
        Size sourceEnd) {
        Size sourceLen = 0;
        if (sourceStart < sourceEnd && sourceEnd < length()) {
            sourceLen = sourceEnd - sourceStart;
        }
        Size copyLen = 0;
        if (sourceLen && targetStart < target->length()) {
            Size max = target->length() - targetStart;
            copyLen = sourceLen < max ? sourceLen : max;
        }
        for (Size i = 0; i < copyLen; i++) {
            UByte value;
            getUInt8(sourceStart + i, &value);
            target->setUInt8(i, value);
        }
    }

 private:
    JsArrayBuffer::Ptr buffer_;

    BufferImpl(Size size) : buffer_(JsArrayBuffer::create(size)) {}

    BufferImpl(JsArrayBuffer::Ptr buf) : buffer_(buf) {}

    LIBJ_JS_ARRAY_BUFFER_IMPL(buffer_);
};

Buffer::Ptr Buffer::create(Size length) {
    return BufferImpl::create(length);
}

Buffer::Ptr Buffer::create(const UByte* data, Size length) {
    return BufferImpl::create(data, length);
}

Buffer::Ptr Buffer::create(String::CPtr str, String::Encoding enc) {
    return BufferImpl::create(str, enc);
}

}  // namespace node
}  // namespace libj