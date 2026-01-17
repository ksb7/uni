import java.util.function.Consumer;

public class Synchronization {
    private int available;
    private Consumer<String> logger;

    public Synchronization(int available, Consumer<String> logger) {
        this.available = available;
        this.logger = logger;
    }

    public synchronized void requestResource(int processId) {
        while (available == 0) {
            log("Procesul " + processId + " așteaptă resurse");
            try { wait(); } catch (InterruptedException e) { e.printStackTrace(); }
        }
        available--;
        log("Procesul " + processId + " a primit o resursă. Resurse libere: " + available);
    }

    public synchronized void releaseResource(int processId) {
        available++;
        log("Procesul " + processId + " a eliberat o resursă. Resurse libere: " + available);
        notifyAll();
    }

    private void log(String mesaj) {
        if (logger != null) {
            logger.accept(mesaj);
        } else {
            System.out.println(mesaj);
        }
    }
}
