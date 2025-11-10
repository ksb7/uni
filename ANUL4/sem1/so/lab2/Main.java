public class Main {

    public static void main(String[] args) throws InterruptedException 
    {

        int X = 3;    // producatori
        int Y = 3;    // consumatori
        int Z = 53;   // total obiecte
        int D = 6;    // capacitatea depozitului

        Depozit depozit = new Depozit(D, Z);

        // pornim producatorii
        for (int i = 1; i <= X; i++) 
        {
            new Producator(depozit, i).start();
        }

        // pornim consumatorii
        for (int i = 1; i <= Y; i++) 
        {
            new Consumator(depozit, i).start();
        }
    }
}
