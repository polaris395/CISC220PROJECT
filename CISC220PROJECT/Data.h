#ifndef DATA_H_
#define DATA_H_

#ifndef NULL
#define NULL 0
#endif

#include <string>
#include <sstream>
using std::string;
using std::stringstream;

class Data {
  public:
    virtual ~Data() {}

    /**
     * Returns 0 if equal to other, -1 if < other, 1 if > other
     */
    virtual int compareTo(Data * other) const = 0;

    /**
     * Returns a string representation of the data
     */
    virtual string toString() const = 0;
};

// An implementation of Data using a single integer
class IntegerData : public Data {
  public:
    int value;

    // This is the syntax for a constructor that initializes the
    // properties value to the parameters
    IntegerData(int value = 0) : value(value) {}

    /**
     * Returns 0 if equal, -1 if < other, 1 if > other
     */
    int compareTo(Data * other) const {
      IntegerData * otherInteger = (IntegerData *)other;
      // ternary operator applies like an if/else:
      // _x_ ? _y_ : _z_
      // is equivalent to
      // if (_x_) { _y_ } else { _z_ }
      return value < otherInteger->value ? -1 : value > otherInteger->value ? 1 : 0;
    }

    /**
     * Returns a string representation of the data
     */
    string toString() const {
      stringstream s;

      // left shift operator for streams takes the value and appends it to the stream
      // in this line of code, the value is placed into a stringstream
      s << value;
      // now we return the string that was created in the stringstream
      return s.str();
    }
};

/**
 * A "tag" interface so that users can interact with
 * the underlying Data structure after adding an item.
 */
class Container {
  public:
    virtual ~Container() {};
};


#endif /* DATA_H_ */
