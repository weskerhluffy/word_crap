:w
package amazonorderid;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class AmazonOrderID {

	public static void main(String[] args) {
		List<String> ids = new ArrayList<>();
		ids.add("4423dd casa miercoles");
		ids.add("32g34 cra push");
		ids.add("c231 few ask dada");
		ids.add("c2312 short");
		ids.add("c2312 short");
		ids.add("c2312 shorts");
		ids.add("po6y56 1111 432");
		ids.add("po6y56 3121 321");
		ids.add("po2y56 3121 321");

		/*
		 * Output: 4423dd casa miercoles 32g34 cra push c231 few ask dada c2312 short
		 * c2312 short c2312 shorts po2y56 3121 321 po6y56 1111 432 po6y56 3121 321
		 */

		orderID(ids);
		for (String s : ids) {
			System.out.println(s);
		}

	}

	public static void orderID(List<String> ids) {
		Collections.sort(ids, new IDComparator());
	}

	public static class IDComparator implements Comparator<String> {

		@Override
		public int compare(String s1, String s2) {
			String s11 = s1.substring(0, s1.indexOf(" "));
			String s21 = s2.substring(0, s2.indexOf(" "));
			String s12 = s1.substring(s1.indexOf(" ") + 1, s1.length());
			String s22 = s2.substring(s2.indexOf(" ") + 1, s2.length());
			if (s1.equals(s2)) {
				return 0;
			}
			/* Letters */
			if (isWord(s12) && isWord(s22)) {
				if (s12.compareTo(s22) == 0) {
					return s11.compareTo(s21);
				} else {
					return s12.compareTo(s22);
				}
			}
			else {
			/* Numbers */
				if(isWord(s12)) {
					return -1;
				}
				else {
					if(isWord(s22))
					{
						return 1;
					}
					else {
						return 0;
					}
				}
			}
			
		
		}

		private boolean isWord(String s) {
			for (Character c : s.toCharArray()) {
				if (Character.isLetter(c) == false && c != ' ') {
					return false;
				}
			}
			return true;
		}
	}

}
