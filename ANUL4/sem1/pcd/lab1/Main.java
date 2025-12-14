import java.util.Random;

public class Main 
{
    static final int N = 100;

    public static void main(String[] args) 
    {

        int[] mas = new int[N];
        Random r = new Random();

        for (int i = 0; i < N; i++) 
        {
            mas[i] = r.nextInt(100) + 1; // valori 1..100
        }

        // Firul 1 – condiția 1
        Thread th1 = new Thread(() -> 
        {
            int suma = 0;
            for (int i = 0; i < mas.length - 1; i += 2) 
            {
                if (mas[i] % 2 == 0 && mas[i+1] % 2 == 0) 
                {
                    suma += mas[i] * mas[i+1];
                }
            }
            System.out.println("Conditia 1 – Suma produselor numerelor pare doua cate doua de la inceput: " + suma);
        });

        // Firul 2 – conditia 2
        Thread th2 = new Thread(() -> 
        {
            int suma = 0;
            for (int i = mas.length - 1; i > 0; i -= 2) 
            {
                if (mas[i] % 2 == 0 && mas[i-1] % 2 == 0) 
                {
                    suma += mas[i] * mas[i-1];
                }
            }
            System.out.println("Conditia 2 – Suma produselor numerelor pare doua cate doua de la sfarsit: " + suma);
        });

        // Pornim firele
        th1.start();
        th2.start();

        try 
        {
            // Asteapta terminarea firelor
            th1.join();
            th2.join();
        } catch (InterruptedException e) 
        {
            e.printStackTrace();
        }

        // Textul studentului afisat litara cu litera
    
        String student = "Lucrarea a fost realizata de studenta: [Cristina Serba]";

        System.out.println("-----");
        for (int i = 0; i < student.length(); i++) 
        {
            System.out.print(student.charAt(i));
            try 
            {
                Thread.sleep(100);
            } catch (InterruptedException e) 
            {
                e.printStackTrace();
            }
        }
        System.out.println();
    }
}
