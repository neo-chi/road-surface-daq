# Rolling Buffer Test

## Problem

### Potential Solutions

### Decision Criteria

## Algorithm



<div style="background-color:rgba(0, 0, 0, 0.3)";/>


```cpp
/**
 * Rolls all accelerometer values left.
 *
 * @note if array length = 10
 *       	max index = 10 - 1
 *
 **/
shift_left(float *buf, size_t len)
{
	//> for a single array...
	float tmp = array[0];

	for (int i = 0; i < len - 1; i++) {}
		array[i] = array[i + 1];
	}

	// assign right-most value to tmp
	array[len - 1] = tmp;
}

```

Now lets implement this algorithm with parameters.
This will let us pass an acceleration axis buffer and left shift it.

```cpp

/**
 * @note	On pointer arithmetic
 *			ptr++ increments address
 *			ptr-- decrements address
 *			ptr + 5 points 5 addresses BEYOND last  element of array
 *			ptr + 5 points 5 addresses BEFORE first element of array
 **/
shift_left(float *buf, size_t len)
{
	//> for a single array...
	//> using pointer arithmetic, get the value of the first item in buf
	float *ptr = buf;

	float tmp = *ptr; // first array element //float tmp = buf[0];

	for (int i = 0; i < len - 1; i++) {
		*ptr = *(ptr++);
	}

	float *address_of_last_elemnt_of_buf =

	while (ptr <=)

	// assign right-most value to tmp
	buf[len - 1] = tmp;
}

```cpp
/**
 *
 */
class RollingBuffer
{
	public:
		RollingBuffer();
		shift_left();
		shift_right();
		float x[];
		float y[];
		float z[]
		~RollingBuffer();
	protected:
	private:
};
```

</div>

////////////////////////////////////////////////////////////////////////////////