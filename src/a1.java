package amazonwordtoexclude;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.TreeSet;

public class AmazonWordToExclude {

	public static void main(String[] args) {
		String text = "2 22 2 It’s some Example about amazon, it’s more, 4 bla bla, some amazon";
		ArrayList<String> wordToExclude = new ArrayList<>(Arrays.asList("some", "S"));
		System.out.println(wordToExclude(text, wordToExclude));
	}

	public static List<String> wordToExclude(String text, List<String> wordToExclude) {
		int begin, end, count;
		String word;
		List<String> words = new ArrayList<>();
		TreeSet<Node> tSet = new TreeSet<>(new TreeComparator());
		LinkedHashMap<String, Node> wantedWords = new LinkedHashMap<>();
		HashSet<String> unwantedWords = new HashSet<>();

		for (String s : wordToExclude) {
			unwantedWords.add(s.toLowerCase());
		}
		/* Parse by using two char pointers */
		for (begin = 0; begin < text.length(); begin++) {
			if (Character.isLetter(text.charAt(begin))) {
				for (end = begin + 1; end < text.length() && Character.isLetter(text.charAt(end)); end++)
					;
				word = text.toLowerCase().substring(begin, end);

				if (unwantedWords.contains(word) == false) {
					if (wantedWords.containsKey(word) == false) {
						Node newNode = new Node(word, 1);
						wantedWords.put(word, newNode);
						tSet.add(newNode);
					} else {
						Node retrievedNode = wantedWords.get(word);
						tSet.remove(retrievedNode);
						retrievedNode.freg++;
						wantedWords.put(word, retrievedNode);
						tSet.add(retrievedNode);
					}
				}
				begin = end;
			}
		}

		/* Fill out the returned list */
		Iterator<Node> it = tSet.iterator();
		int max = -1;
		while (it.hasNext()) {
			Node n = it.next();
			if (max == -1) {
				words.add(n.word);
				max = n.freg;
			} else {
				if (max > n.freg) {
					break;
				}
				words.add(n.word);
			}
		}

		return words;
	}

	public static class TreeComparator implements Comparator<Node> {

		@Override
		public int compare(Node n1, Node n2) {
			if (n1 == n2 || n1.word.equals(n2.word)) {
				return 0;
			}
			return n1.freg > n2.freg ? -1 : 1;
		}
	}

	public static class Node {

		String word;
		int freg;

		Node(String word, int freq) {
			this.word = word;
			this.freg = freq;
		}
	}

}
