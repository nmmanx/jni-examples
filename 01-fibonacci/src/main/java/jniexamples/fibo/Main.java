package jniexamples.fibo;

public class Main {

    public static void main(String[] args) {
        int n;
        int algo = Fibonacci.ALGO_RECURSION;

        if (args.length > 0) {
            n = Integer.parseInt(args[0]);
        } else {
            return;
        }

        if (args.length >= 1) {
            algo = Integer.parseInt(args[1]);
        }

        switch(algo) {
        case Fibonacci.ALGO_RECURSION:
            System.out.println("Selected recursion algorithm");
            break;
        case Fibonacci.ALGO_DYNAMIC:
            System.out.println("Selected dynamic programming algorithm");
            break;
        default:
            System.out.println("Invalid algorithm");
            return;
        }

        System.out.println("Result: " + String.valueOf(Fibonacci.fibo(n, algo)));
    }
}
