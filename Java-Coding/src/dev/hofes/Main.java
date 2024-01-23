package dev.hofes;

import dev.hofes.SEN.BinaryTrees.Tree;

public class Main {
    public static void main(String[] args) {


        Tree<Integer> tree = new Tree<>();
        tree.insert(5);
        tree.insert(4);
        tree.insert(3);
        tree.insert(2);
        tree.insert(1);

        for (Integer i : tree) {
            System.out.println(i);
        }


        /*WaitingRoom w = new WaitingRoom();
        new Doc(w, 1000).start();
        new Doc(w, 900).start();

        w.start();/**/

    /*Stack stack = new Stack(3);
    try {
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
    } catch (Stack.StackOverflowException e) {
        System.out.println(e.getMessage());
    }/**/

/*
        Tokenizer tokenizer = new Tokenizer("Hello World! How are you?");
        for (String e : tokenizer) System.out.println(e);/**/

        /*DataSet ds = new DataSet(4);
        ds.add(1);
        ds.add(2);
        ds.add(3);
        ds.add(4);
        for (Object o : ds) {
            System.out.println(o);
        }/**/

        /*Dictionary dictionary = new Dictionary();
        Scanner s = new Scanner(System.in);
        String line;
        while (!(line = s.nextLine()).equals(".")) {
            String[] split = line.split(" ");
            dictionary.insert(split[0], split[1]);
        }

        line = s.nextLine();
        String[] split = line.split(" ");
        for (String w : split) {
            System.out.print(dictionary.lookupGermanWord(w) + " ");
        }

        for (Entry e : dictionary) {
            System.out.println(e);
        }/**/

        /*SortedList list = new SortedList();
        Scanner s = new Scanner(Path.of("Top100.txt"));
        while (s.hasNext()) {
            String line = s.nextLine();
            String[] split = line.split("\"");
            List<String> l = Arrays.stream(split).map(String::trim).toList();

            list.insert(l.get(1), Long.parseLong(l.get(2)));
        }

        for (Person person : list) {
            System.out.println(person);
        }

        System.out.println("\n------------ between 100m and 500m ------------\n");
        SortedList subList = list.sublist(100000000, 500000000);
        for (Person person : subList) {
            System.out.println(person);
        }/**/

        /*StateList stateList = new StateList();
        Scanner s = new Scanner(Path.of("EU_Debts.txt"));
        while (s.hasNext()) {
            stateList.insert(s.next(), s.nextDouble());
        }

        for (State state : stateList) {
            System.out.println(state.getName() + ": " + state.getDebt());
        }

        System.out.println(StateList.upTo(stateList, 25D));
        System.out.println(StateList.between(stateList, 25D, 50D));
        System.out.println(StateList.between(stateList, 50D, 75D));
        System.out.println(StateList.between(stateList, 75D, 100D));
        System.out.println(StateList.between(stateList, 100D, 125D));
        System.out.println(StateList.greaterThan(stateList, 125D));*/


        /*List<Integer> l = new List<>();

        l.add(3);
        l.add(2);
        l.add(4);
        l.add(1);

        l.print();/**/

        /*List<String> l = new List<>();

        l.add("adg");
        l.add("dfvhsfg");
        l.add("tnkdbjhytv");
        l.add("1ersvgca");

        l.print();/**/


        //Random rand = new Random();
        //int[] arr = new int[]{1, 2, 3, 4, 5, 6};

        /*int[] a = Split.main(84, 82);

        System.out.println(sum(a) + " = " + Arrays.toString(a));*/


        /*Rectangle[] rects = new Rectangle[7];
        for (int i = 0; i < rects.length; i++)
            rects[i] = new Rectangle(rand.nextInt(50) + 1, rand.nextInt(50) + 1,
                    rand.nextInt(50) + 1, rand.nextInt(50) + 1);

        for (Rectangle r : rects) {
            int x = rand.nextInt(50) + 1, y = rand.nextInt(50) + 1;
            System.out.println(r.isHit(x, y));
            System.out.println(x);
            System.out.println(y);
            System.out.println(r);
        }*/

        /*String[] s = new String[]{"Hi", "I", "am", "Felix"};
        RightJustified.main(s);
        for (String a : s) System.out.println(a);*/

        //CountWords.main();

        /*WaltersList list = new WaltersList();
        list.addFine("A", "1a", 1);
        list.addFine("B", "2a", 5);
        list.addFine("C", "3a", 3);
        list.addFine("D", "3a", 3);
        list.addFine("D", "3a", 3);
        list.sortByAmount();
        list.printList();
        list.printAmountByClass("3a");
        System.out.println(list.getAmountByClass("3a"));*/

        /*String s = "Hello, i am me.";
        System.out.println(Snippets.toUpper(s, "am"));
        System.out.println(s);*/

        /*Zaehler z = new Zaehler("ÄpFeL", 9);
        z.print();
        z.print("Es sind %n %b im Korb");*/

        /*System.out.println(Substr.main("Hello", 1, 2));
        System.out.println("Hello".substring(1, 2));*/


        //System.out.println(LongestCommonSuffix.main("Helload", "Helloa"));

        /*System.out.println(Zahlentext.stringToNums("ABCXYZ"));
        System.out.println(Zahlentext.numsToString(Zahlentext.stringToNums("ABCXYZ")));*/

        //System.out.println(ROT13.main("SFFG"));

        //System.out.println(Genetik.main("tttcaagctgcggtaatcggtagatccccggtacggtacggtaagct"));

        /*SatzUndWort s = new SatzUndWort("Hallo, ich bin ich", "ich");
        System.out.println(s.remove());
        System.out.println(s.getSentence());*/

        //System.out.println(Palindrom.isPalindrome("anaana"));
        //CountWords.main();

        /*StringSplit s = new StringSplit("abcdefghij", 4);
        while (s.hasMoreChunks())
            System.out.println(s.nextChunk());*/

    }

    /*private static int sum(int @NotNull [] arr) {
        int s = 0;
        for (int v : arr)
            s += v;
        return s;
    }*/
}