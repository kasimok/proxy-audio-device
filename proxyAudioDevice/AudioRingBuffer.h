#ifndef __AudioRingBuffer_h__
#define __AudioRingBuffer_h__

#include <CoreServices/CoreServices.h>

// used for now to cache a couple of seconds (?) of input and access it for audio thruing
class AudioRingBuffer {
  public:
    AudioRingBuffer(UInt32 bytesPerFrame, UInt32 capacityFrames);
    ~AudioRingBuffer();

    void Allocate(UInt32 bytesPerFrame, UInt32 capacityFrames);
    void Clear();
    bool Store(const Byte *data, UInt32 nFrames, SInt64 frameNumber);
    bool Fetch(Byte *data, UInt32 nFrames, SInt64 frameNumber);

    UInt32 FrameOffset(SInt64 frameNumber) {
        return (mStartOffset + UInt32(frameNumber - mStartFrame) * mBytesPerFrame) % mCapacityBytes;
    }

    //    number of bytes per sampled audio frame, which is the
    //    smallest unit of data structure in the ring buffer
    UInt32 mBytesPerFrame;
    
    //    the capacity of the ring buffer in the unit of sampled audio frames
    UInt32 mCapacityFrames;
    
    //    the capacity of the ring buffer in the unit of bytes
    UInt32 mCapacityBytes;
    
    //    main Byte array
    Byte *mBuffer;
    
    
    UInt32 mStartOffset;
    
    //    position of the starting frame
    SInt64 mStartFrame;
    
    //    position of the end frame
    SInt64 mEndFrame;
};

#endif // __AudioRingBuffer_h__
