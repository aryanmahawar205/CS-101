import java.util.*;

public class StrobogrammaticCheck {
    public static boolean isStrobogrammatic(String num) {
        Map<Character, Character> map = new HashMap<>();
        map.put('0', '0');
        map.put('1', '1');
        map.put('8', '8');
        map.put('6', '9');
        map.put('9', '6');

        int i = 0, j = num.length() - 1;

        while (i <= j) {
            char left = num.charAt(i);
            char right = num.charAt(j);

            if (!map.containsKey(left)) {
                return false;
            }
            if (map.get(left) != right) {
                return false;
            }

            i++;
            j--;
        }
        return true;
    }

    // Quick test
    public static void main(String[] args) {
        System.out.println(isStrobogrammatic("69"));  // true
        System.out.println(isStrobogrammatic("88"));  // true
        System.out.println(isStrobogrammatic("962")); // false
    }
}