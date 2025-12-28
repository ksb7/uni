import javax.swing.*;
import java.awt.*;

public class FCIMSpotGUI extends JFrame
{
    private static volatile boolean running = true;
    private static final Object lock = new Object();

    private JTextArea textArea;

    public FCIMSpotGUI()
    {
        setTitle("FCIM Spot Publicitar");
        setSize(700, 450);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        textArea = new JTextArea();
        textArea.setEditable(false);

        textArea.setFont(new Font("SansSerif", Font.BOLD, 26));
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        textArea.setBackground(Color.BLACK);
        textArea.setForeground(Color.GREEN);

        add(new JScrollPane(textArea), BorderLayout.CENTER);
        setVisible(true);

        startThreads();
    }

    private void startThreads()
    {
        // Thread pentru mesajul principal
        Thread mainMessage = new Thread(() ->
        {
            String message = "Bine ati venit la FCIM";
            boolean wasRunning = false;

            while (true)
            {
                if (running && !wasRunning)
                {
                    clearAndPrintSlow(message, 150);
                    wasRunning = true;
                }
                else if (!running)
                {
                    wasRunning = false;
                    sleep(100);
                }
            }
        });

        // Thread pentru mesajele secundare
        Thread secondaryMessage = new Thread(() ->
        {
            String[] slogans =
            {
                "Facultatea Calculatoare, Informatica si Microelectronica",
                "Inovatie si tehnologie la tine aproape",
                "Alatura-te comunitatii FCIM"
            };

            int index = 0;

            while (true)
            {
                if (running)
                {
                    clearAndPrintSlow(slogans[index], 100);
                    index = (index + 1) % slogans.length;
                }
                else
                {
                    sleep(100);
                }
            }
        });

        // Thread care porneste si opreste spotul automat
        Thread control = new Thread(() ->
        {
            while (true)
            {
                sleep(5000);
                running = !running;
            }
        });

        mainMessage.start();
        secondaryMessage.start();
        control.start();
    }

    // Sterge textul si apoi il afiseaza caracter cu caracter
    private void clearAndPrintSlow(String text, int delayMs)
    {
        synchronized (lock)
        {
            clearText();

            for (char c : text.toCharArray())
            {
                appendText(String.valueOf(c));
                sleep(delayMs);
            }
        }
    }

    // Sterge complet zona de afisare
    private void clearText()
    {
        SwingUtilities.invokeLater(() ->
        {
            textArea.setText("");
        });
    }

    // Adauga textul in siguranta pentru Swing
    private void appendText(String text)
    {
        SwingUtilities.invokeLater(() ->
        {
            textArea.append(text);
        });
    }

    // Pauza simpla folosita de thread-uri
    private static void sleep(int ms)
    {
        try
        {
            Thread.sleep(ms);
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(FCIMSpotGUI::new);
    }
}
