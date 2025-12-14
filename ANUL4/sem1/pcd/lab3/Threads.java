public class Threads 
{

    private static final Object lock = new Object(); // pentru sincronizare afisare

    public static void main(String[] args) 
    {

        // Thread 1: Conditia 1
        Thread Th1 = new Thread(() -> 
        {
            int suma = 0;
            for (int i = 200; i <= 300; i += 2) 
            {
                if (i + 2 <= 300) 
                {
                    suma += i * (i + 2);
                }
            }
            synchronized(lock) 
            {
                System.out.println("Th1 - Conditia 1: Suma finala = " + suma);
                printSlow("Prenume: Cristina", 100);
            }
        }, "Th1");

        // Thread 2: Conditia 2
        Thread Th2 = new Thread(() -> 
        {
            int suma = 0;
            for (int i = 106; i >= 6; i -= 2) 
            {
                if (i - 2 >= 6) 
                {
                    suma += i * (i - 2);
                }
            }
            synchronized(lock) 
            {
                System.out.println("Th2 - Conditia 2: Suma finala = " + suma);
                printSlow("Nume: Serba", 100);
            }
        }, "Th2");

        // Thread 3: Conditia 3
        Thread Th3 = new Thread(() -> 
        {
            System.out.println("Th3 - Conditia 3: ");
            synchronized(lock) 
            {
                for (int i = 234; i <= 1000; i++) {System.out.print(" " + i);}
                System.out.println("\nTh3 - Conditia 3: Finalizat");
                printSlow("Disciplina: Programarea concurenta si distribuita", 100);
            }
        }, "Th3");

        // Thread 4: Conditia 4
        Thread Th4 = new Thread(() -> 
        {
            System.out.println("Th4 - Conditia 4: ");
            synchronized(lock) 
            {
                for (int i = 1234; i >= 456; i--) {System.out.print(" " + i);}
                System.out.println("\nTh4 - Conditia 4: finalizat");
                printSlow("Grupa: CR-221FR", 100);
            }
        }, "Th4");

        // Pornire thread-uri
        Th1.start();
        Th2.start();
        Th3.start();
        Th4.start();

        // Asteptam terminarea tuturor thread-urilor
        try 
        {
            Th1.join();
            Th2.join();
            Th3.join();
            Th4.join();
        } catch (InterruptedException e) 
        {
            e.printStackTrace();
        }
    }

    // Functie pentru afisare caracter cu caracter
    private static void printSlow(String text, int delayMs) 
    {
        for (char c : text.toCharArray()) 
        {
            System.out.print(c);
            try { Thread.sleep(delayMs); } catch (InterruptedException e) {}
        }
        System.out.println();
    }
}
