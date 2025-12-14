public class FCIMSpot 
{
    private static volatile boolean running = true; // controleaza daca spotul ruleaza
    private static final Object lock = new Object(); // lock pentru afisare sincronizata

    public static void main(String[] args)
    {
        // Thread 1: Mesaj principal
        Thread mainMessage = new Thread(() -> 
        {
            String message = "Bine ati venit la FCIM";
            boolean wasRunning = false;
            while (true) 
            {
                if (running && !wasRunning) 
                { // afișam doar daca tocmai s-a repornit
                    printSlow(message, 150);
                    wasRunning = true;
                } else if (!running)
                {
                    wasRunning = false; // resetam cand spotul este intrerupt
                    sleep(100);
                }
            }
        }, "MainMessage");


        // Thread 2: Mesaje secundare / sloganuri
        Thread secondaryMessage = new Thread(() -> 
        {
            String[] slogans = {
                    "Facultatea Calculatoare, Informatica si Microelectronica",
                    "Inovatie si tehnologie la tine aproape",
                    "Alatura-te comunitatii FCIM"
            };
            int index = 0;
            while (true) 
            {
                if (running) 
                {
                    printSlow(slogans[index], 100);
                    index = (index + 1) % slogans.length;
                } else 
                {
                    sleep(100); // pauza scurta
                }
            }
        }, "SecondaryMessage");

        // Thread 3: Control spot (pauza / repornire)
        Thread control = new Thread(() ->
        {
            while (true) 
            {
                sleep(5000); // la fiecare 5 secunde schimbam starea
                running = !running;
                synchronized(lock) 
                {
                    if (running) 
                    {
                        System.out.println("\n=== Spot repornit ===\n");
                    } else {
                        System.out.println("\n=== Spot intrerupt ===\n");
                    }
                }
            }
        }, "Control");

        // Pornim toate firele
        mainMessage.start();
        secondaryMessage.start();
        control.start();
    }

    // Functie pentru afisare caracter cu caracter, sincronizata
    private static void printSlow(String text, int delayMs) 
    {
        synchronized(lock)
        {   // blocheaza consola pentru un mesaj complet
            for (char c : text.toCharArray()) 
            {
                System.out.print(c);
                sleep(delayMs);
            }
            System.out.println();
        }
    }

    // Functie de sleep care ignora InterruptedException
    private static void sleep(int ms) 
    {
        try 
        {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
