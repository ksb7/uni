package InterfataGrafica;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;

public class Main {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FereastraMea fer=new FereastraMea("Meniu Utilizator");
        MeniuUtilizator meniu = new MeniuUtilizator(); 
        fer.add(meniu);
        meniu.panouPrincipal();
        /*afisarea ferestrei*/
        fer.setVisible(true);
	}
}