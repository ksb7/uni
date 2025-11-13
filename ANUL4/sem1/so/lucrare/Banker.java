public class Banker 
{
    public static void main(String[] args) 
    {
        int X = 8;  // numărul proceselor
        int Y = 11; // numărul resurselor

        System.out.println("=== Test cu STARE STABILĂ ===");
        StableState stable = new StableState(X, Y);
        if (stable.isSafeState())
            System.out.println("Sistemul este intr-o stare sigura");
        else
            System.out.println("Sistemul este intr-o stare nesigura");
        stable.runThreads();

        System.out.println("\n=== Test cu STARE NESTABILĂ ===");
        UnstableState unstable = new UnstableState(X, Y);
        if (unstable.isSafeState())
            System.out.println("Sistemul este intr-o stare sigura");
        else
            System.out.println("Sistemul este intr-o stare nesigura");
        unstable.runThreads();
    }
}
