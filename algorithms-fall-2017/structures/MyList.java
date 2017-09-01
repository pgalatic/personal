/**
 * @author Paul Galatic (pdg6505@g.rit.edu)
 *
 * Implements a list in Java. */

public class MyArray<T> {
	private int length = 0;
    private int size = 0;
    private static final int DEFAULT_SIZE = 16;
	private Object elements[];

    /** Creates a new List of the default length. */
	public MyList(){
		elements = new Object[DEFAULT_SIZE];
        size = DEFAULT_SIZE;
	}

    /** Creates a new List of a specified length. */
    public MyList(int size){
        if (size < 2){
            System.out.println("WARN: Size too low. Using default size.");
            return new MyList();
        }
        elements = new Object[size];
        this.size = size;
    }

    /** Appends an object to the back of the list. */
    public void Append(T element){
        if (size == length){ Grow(); }
        elements[length++] = element;
    }

    /** Inserts an element at a point in the list. */
    public void Insert(T element, int index){
        T array[];
        if (size == length){ size *= 2; }
        array = new T[size];

        for (int x = 0; x < index; x++){
            array[x] = elements[x];
        }
        array[index] = element;
        for (int x = index; x < length; x++){
            array[x + 1] = elements[x];
        }

        elements = array;
        length++;
    }

    /** Removes and returns the element at the top of the list. */
    @SuppressWarnings("unchecked") // get outta here
    public T Pop(){
        Object element = elements[length];
        elements[length--] = null;
        return (T)element;
    }

    /** Removes and returns an element at a point in the list. */
    @SuppressWarnings("unchecked") // get outta here
    public T Remove(int index){
        T array[] = new T[length];
        for (int x = 0; x < index; x++){
            array[x] = elements[x];
        }
        T element = (T)elements[index];
        for (int x = index + 1; x < length; x++){
            array[x - 1] = elements[x];
        }
        elements = array;
        length--;
        return element;
    }

    /** Returns the element at the specified index. */
    @SuppressWarnings("unchecked") // get outta here
    public T Get(int index){
        return (T)elements[index];
    }

    /** Returns the length of the array. */
    public int Length(){
        return length;
    }

    /** Increases the size of the array by a factor of two. */
    private void Grow(){
        size *= 2;
        T array[] = new T[size];
        for (int x = 0; x < length; x++){
            array[x] = elements[x];
        }
        elements = array;
    }
}
