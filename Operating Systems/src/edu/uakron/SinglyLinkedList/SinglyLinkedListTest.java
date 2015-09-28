package edu.uakron.SinglyLinkedList;

import java.util.Arrays;

/**
 * Tests for SinglyLinkedList
 */
public class SinglyLinkedListTest {
    public static void main(String[] args) {
        // Default constructor.
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        assertThat(list.getHead() == null, "Head should be null.");
        assertThat(list.size() == 0, "Size should be 0.");

        // Alternative constructor.
        Integer[] ints = new Integer[]{1, 2, 3, 4, 5};
        list = new SinglyLinkedList<>(ints);
        assertThat(list.getHead().getValue() == 1, "Head should be 1.");
        assertThat(list.size() == 5, "Size should be 5.");

        SinglyLinkedList<String> pizza = new SinglyLinkedList<>();
        // Insert
        assertThat(pizza.size() == 0, "Size should be 0.");
        pizza.insert("Cheese");
        pizza.insert("Pepperoni");
        pizza.insert("Mushrooms");
        assertThat(pizza.size() == 3, "Size should be 3.");
        // Insert at index
        assertThat(pizza.get(1).equals("Pepperoni"), "Index '1' should be 'Pepperoni'");
        pizza.insert(1, "Banana Peppers");
        assertThat(pizza.size() == 4, "Size should be 4.");
        assertThat(pizza.get(1).equals("Banana Peppers"), "Index '1' should be 'Banana Peppers'");
        // Remove at index
        pizza.removeAtIndex(2);
        assertThat(pizza.size() == 3, "Size should be 3.");
        // To array
        String[] strings = new String[]{"First", "Second", "Third"};
        SinglyLinkedList<String> stringsList = new SinglyLinkedList<>(strings);
        Object[] expectedStrings = stringsList.toArray();
        assertThat(Arrays.equals(strings, expectedStrings), "Arrays are not equal.");
        // Get
        String toppingOne = pizza.get(0);
        String toppingTwo = pizza.get(1);
        assertThat(toppingOne.equals("Cheese"), "First string should be 'Cheese'");
        assertThat(toppingTwo.equals("Banana Peppers"), "Second string should be 'Mushrooms'");
        // Index of
        int index = pizza.indexOf("Mushrooms");
        assertThat(index == 2, "Index of Mushrooms should be 2");
        index = pizza.indexOf("Cheese");
        assertThat(index == 0, "Index of Cheese should be 0");
        index = pizza.indexOf("Pepperoni");
        assertThat(index == -1, "Pepperoni shouldn't exist in list.");
        // Is Empty
        assertThat(!pizza.isEmpty(), "List should not be empty.");
        // Clear
        pizza.clear();
        assertThat(pizza.isEmpty(), "List should be empty.");
    }

    private static void assertThat(boolean bool, String str) {
        if (!bool) {
            System.out.println(str);
        }
    }
}
