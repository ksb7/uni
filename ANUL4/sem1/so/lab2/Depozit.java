import java.util.LinkedList;
import java.util.Queue;

public class Depozit 
{
    private final int capacitate;
    private Queue<Character> buffer = new LinkedList<>();

    public int produseTotale = 0;
    public int consumateTotale = 0;
    public final int Z;

    public Depozit(int capacitate, int Z) 
    {
        this.capacitate = capacitate;
        this.Z = Z;
    }

    // sincronizare producere
    public synchronized void produce(char a, char b, int id) throws InterruptedException 
    {
        while (buffer.size() + 2 > capacitate) 
        {
            System.out.println("Depozitul e plin, producatorul " + id + " asteapta...");
            wait();
        }

        if (produseTotale < Z) 
        {
            buffer.add(a);
            buffer.add(b);
            produseTotale += 2;

            System.out.println("Producatorul " + id + " a produs: " + a + " " + b);
            System.out.println("In depozit sunt acum " + buffer.size() + " obiecte.");
        }

        notifyAll();
    }

    // sincronizare consumare
    public synchronized char[] consume(int id) throws InterruptedException 
    {
        while (buffer.size() < 2) 
        {
            if (consumateTotale >= Z) return null;
            System.out.println("Depozitul e gol, consumatorul " + id + " asteapta...");
            wait();
        }

        if (consumateTotale >= Z) return null;

        char a = buffer.poll();
        char b = buffer.poll();
        consumateTotale += 2;

        System.out.println("Consumatorul " + id + " a consumat: " + a + " " + b);
        System.out.println("In depozit au ramas " + buffer.size() + " obiecte.");

        notifyAll();
        return new char[]{a, b};
    }
}
