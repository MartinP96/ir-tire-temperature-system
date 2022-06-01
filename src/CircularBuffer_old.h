#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

class CircularBuffer
{
public:

  // Constructor
  CircularBuffer(int _buffer_size);

  // Public methods
  void writeToBuffer(float _data);
  void readFromBuffer(float* data_element);
  int numberOfElements();


  bool getBufferFullStatus(void) {return buffer_full;}
  int getBufferSizeStatus(void) {return buffer_size;}

private:

  // Praivate methods
  bool isBufferEmpty();

  // Private variables
  float* buffer;
  int read_ptr;
  int write_ptr;
  bool buffer_full;
  int buffer_size;


};

#endif
