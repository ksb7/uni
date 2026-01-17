import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class BankerGUI extends JFrame {

    private JButton startButton;
    private JPanel resourcesPanel;
    private JPanel activeProcessesPanel;
    private JPanel waitingProcessesPanel;
    private JPanel releasedProcessesPanel;

    private List<JPanel> resourcePanels = new ArrayList<>();
    private List<JPanel> activePanels = new ArrayList<>();
    private List<JPanel> waitingPanels = new ArrayList<>();
    private List<JPanel> releasedPanels = new ArrayList<>();

    private int totalProcesses = 8;
    private int totalResources = 11;

    public BankerGUI() {
        setTitle("Algoritmul Banker");
        setSize(1000, 700);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        startButton = new JButton("Start simulare");
        startButton.addActionListener(e -> startSimulation());
        add(startButton, BorderLayout.SOUTH);

        // Resurse
        resourcesPanel = new JPanel(new GridLayout(1, totalResources, 5, 5));
        for (int i = 0; i < totalResources; i++) {
            JPanel r = new JPanel();
            r.setBackground(Color.GREEN);
            r.setBorder(BorderFactory.createLineBorder(Color.BLACK));
            resourcesPanel.add(r);
            resourcePanels.add(r);
        }
        add(resourcesPanel, BorderLayout.NORTH);

        // Procese active
        activeProcessesPanel = new JPanel(new GridLayout(totalProcesses, 1, 5, 5));
        activeProcessesPanel.setBorder(BorderFactory.createTitledBorder("Procese care au primit resurse"));
        for (int i = 0; i < totalProcesses; i++) {
            JPanel p = new JPanel();
            p.setBackground(Color.LIGHT_GRAY);
            p.setBorder(BorderFactory.createTitledBorder("Proces " + (i + 1)));
            activeProcessesPanel.add(p);
            activePanels.add(p);
        }

        // Procese în așteptare
        waitingProcessesPanel = new JPanel(new GridLayout(totalProcesses, 1, 5, 5));
        waitingProcessesPanel.setBorder(BorderFactory.createTitledBorder("Procese în așteptare"));
        for (int i = 0; i < totalProcesses; i++) {
            JPanel p = new JPanel();
            p.setBackground(Color.LIGHT_GRAY);
            p.setBorder(BorderFactory.createTitledBorder("Proces " + (i + 1)));
            waitingProcessesPanel.add(p);
            waitingPanels.add(p);
        }

        // Procese care au eliberat resurse
        releasedProcessesPanel = new JPanel(new GridLayout(totalProcesses, 1, 5, 5));
        releasedProcessesPanel.setBorder(BorderFactory.createTitledBorder("Procese care au eliberat resurse"));
        for (int i = 0; i < totalProcesses; i++) {
            JPanel p = new JPanel();
            p.setBackground(Color.LIGHT_GRAY);
            p.setBorder(BorderFactory.createTitledBorder("Proces " + (i + 1)));
            releasedProcessesPanel.add(p);
            releasedPanels.add(p);
        }

        // Container pentru procese
        JPanel processesContainer = new JPanel(new GridLayout(3, 1));
        processesContainer.add(activeProcessesPanel);
        processesContainer.add(waitingProcessesPanel);
        processesContainer.add(releasedProcessesPanel);

        add(processesContainer, BorderLayout.CENTER);
    }

    private void startSimulation() {
        startButton.setEnabled(false);

        // Logger pentru GUI
        Consumer<String> logger = this::updateGUI;

        StableState stable = new StableState(totalProcesses, totalResources, logger);
        stable.runThreads();

        UnstableState unstable = new UnstableState(totalProcesses, totalResources, logger);
        unstable.runThreads();
    }

    private void updateGUI(String msg) {
        SwingUtilities.invokeLater(() -> {
            if (msg.contains("Procesul")) {
                int id = Integer.parseInt(msg.split(" ")[1]);
                JPanel active = activePanels.get(id - 1);
                JPanel waiting = waitingPanels.get(id - 1);
                JPanel released = releasedPanels.get(id - 1);

                if (msg.contains("rulează")) {
                    active.setBackground(Color.GREEN);
                    waiting.setBackground(Color.LIGHT_GRAY);
                    released.setBackground(Color.LIGHT_GRAY);
                } else if (msg.contains("asteapta") || msg.contains("așteaptă")) {
                    waiting.setBackground(Color.RED);
                    active.setBackground(Color.LIGHT_GRAY);
                    released.setBackground(Color.LIGHT_GRAY);
                } else if (msg.contains("a eliberat")) {
                    released.setBackground(Color.BLUE);
                    active.setBackground(Color.LIGHT_GRAY);
                    waiting.setBackground(Color.LIGHT_GRAY);
                }
            }

            if (msg.contains("Resurse libere")) {
                int available = Integer.parseInt(msg.replaceAll("[^0-9]", ""));
                for (int i = 0; i < resourcePanels.size(); i++) {
                    resourcePanels.get(i).setBackground(i < available ? Color.GREEN : Color.RED);
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new BankerGUI().setVisible(true));
    }
}
