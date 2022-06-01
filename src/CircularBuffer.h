/*
*	title: Circular buffer class
*	date: 21.03.2021
*	created by: Martin P.
*/

#ifndef _CIRCURAL_BUFFER_H_
#define _CIRCURAL_BUFFER_H_

template <typename T>
class CircuralBuffer
{
public:

	// Constructor
	CircuralBuffer(int bufferSize) :buffer_size_{ bufferSize } {
		buffer_ = new T[bufferSize];
		for (int i = 0; i < bufferSize; i++)
		{
			buffer_[i] = 0;
		}
	}

	// Destructor
	~CircuralBuffer()
	{
		delete[] buffer_;
	}

	// Method for writing data to the buffer
	void writeToBuffer(T data)
	{
		if (!buffer_full_)	// If buffer not full - write data to buffer
		{
			buffer_[write_ptr_] = data;
			write_ptr_ = (write_ptr_ + 1) % buffer_size_;  // increment write pointer
			if (read_ptr_ == write_ptr_)
			{
				buffer_full_ = true;
			}
		}
	}

	// Method for reading data from the buffer
	void readFromBuffer(T* data)
	{
		if (!isBufferEmpty())
		{
			*data = buffer_[read_ptr_];
			read_ptr_ = (read_ptr_ + 1) % buffer_size_;  // increment read pointer
			buffer_full_ = false;
		}
	}

	void clearBuffer()
	{
		read_ptr_ = 0;
		write_ptr_ = 0;
		buffer_full_ = false;
	}


	// Check if buffer is empty
	bool isBufferEmpty()
	{
		return ((read_ptr_ == write_ptr_) && !buffer_full_);
	}

	// Check if buffer is full
	bool isBufferFull()
	{
		return buffer_full_;
	}

	// Return number of elements in buffer
	int numberOfElements()
	{
		if (!isBufferEmpty())
		{
			return write_ptr_ - read_ptr_;
		}
		else
		{
			return 0;
		}
	}

	int getBufferSize()
	{
		return buffer_size_;
	}


private:

	//Private variables
	T* buffer_;
	bool buffer_full_;
	int read_ptr_;
	int write_ptr_;
	int buffer_size_;
};

#endif
