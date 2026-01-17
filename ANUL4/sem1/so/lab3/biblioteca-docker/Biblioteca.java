import java.util.ArrayList;
import java.util.List;

public class Biblioteca 
{
    private List<String> carti = new ArrayList<>();
    private int scriitoriRamasi;

    public Biblioteca(int totalScriitori) 
    {
        this.scriitoriRamasi = totalScriitori;
    }

    public synchronized void adaugaCarte(String carte) 
    {
        carti.add(carte);
        System.out.println("Scriitor a adăugat cartea: " + carte);
        notifyAll();
    }

    public synchronized void scriitorTerminat() 
    {
        scriitoriRamasi--;
        notifyAll(); // trezeste cititorii ramasi
    }

    public synchronized String citesteCarte() 
    {
        while (carti.isEmpty()) 
        {
            if (scriitoriRamasi == 0) 
            {
                return null; // nu mai sunt carti si nici scriitori
            }
            try { wait(); } catch (InterruptedException e) {}
        }
        String carte = carti.remove(0);
        System.out.println("Cititor a citit cartea: " + carte);
        notifyAll(); // trezeste ceilalti cititori ramasi
        return carte;
    }
}
