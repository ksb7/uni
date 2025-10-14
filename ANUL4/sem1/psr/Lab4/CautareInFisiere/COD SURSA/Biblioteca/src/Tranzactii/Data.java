package Tranzactii;

import java.util.StringTokenizer;

/**
 * 
 * Clasa <B>Data</B> este folosita pentru stocarea de date. 
 * Instantele acestei clase sunt folosite pentru manipularea datelor calendaristice din cadrul programului.
 * 
 */
public class Data {
	private int zi,luna,an;
	
	/**
	 * Construieste un nou obiect de tip Data care ia ca argument un String si il imparte in zi, luna, an.
	 * String-ul dat ca parametru trebuie sa fie de forma "Z.L.A", unde Z, L, A sunt numere intregi reprezentand ziua, luna si anul.
	 *   
	 * @param dt - un sir de caractere care urmeaza a fi convertit in data
	 */
	public Data(String dt)
	{
		StringTokenizer d=new StringTokenizer(dt,".");
		zi=Integer.parseInt(d.nextToken());
		luna=Integer.parseInt(d.nextToken());
		an=Integer.parseInt(d.nextToken());
	}
	/**
	 * Construieste un nou obiect de tip Data care ia ca argument 3 intregi reptezentand ziua, luna si anul.
	 *   
	 * @param zz - intreg care reprezinta ziua
	 * @param ll - intreg care reprezinta luna
	 * @param aa - intreg care reprezinta anul
	 */
	public Data(int zz,int ll,int aa)
	{
		zi=zz;
		luna=ll;
		an=aa;
	}
	
	/**
	 * Converteste data in String.
	 * 
	 * @return sirul de caractere rezultat in urma convertirii datei
	 */
	public String toString()
	{
		return zi+"."+luna+"."+an;
	}

	/**
	 * Intoarce ziua din data curenta.
	 * 
	 * @return zi - ziua din cadrul datei
	 */
	public int getZi() {
		return zi;
	}

	/**
	 * Intoarce luna din data curenta.
	 * 
	 * @return luna - luna din cadrul datei
	 */
	public int getLuna() {
		return luna;
	}

	/**
	 * Intoarce anul din data curenta.
	 * 
	 * @return an - anul din cadrul datei
	 */
	public int getAn() {
		return an;
	}

	/**
	 * Compara doua date.
	 * Intoarce:
	 * -1 -> data curenta e mai mica decat cea trimisa ca parametru
	 *  0 -> data curenta e egala cu cea trimisa ca parametru
	 *  1 -> data curenta e mai mare decat cea trimisa ca parametru
	 *  
	 * @param dt - data cu care este comparata data curenta
	 * 
	 * @return -1/0/1 in functie de egalitatea sau inegaliatea celor doua date
	 */
	public int ComparaData(Data dt)
	{
		if(an==dt.getAn()) {
			if(luna==dt.getLuna())
				if(zi==dt.getZi())
					return 0;
				else if(zi<dt.getZi())
					return -1;
				else return 1;
			else if(luna<dt.getLuna())
				return -1;
			else return 1;
		} 
		else if(an<dt.getAn())
			return -1;
		else return 1;
	}
			
	public static String DataCurenta(String dt)
	{		
		return dt;
	}
	
	/**
	 * zilele unu an obisnuit
	 */
	static final int[] zileLA = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	/**
	 * Adauga la o data un anumit numar de zile.
	 * 
	 * @param dt - data la care sunt adaugate zilele
	 * @param nrZile - numarul de zile care urmeaza a fi adaugat datei
	 *  
	 * @return o noua data obtinuta din adaugarea a nrZile de zile la data initiala dt
	 */
	public static Data addToZi(Data dt, int nrZile) {
		
		if(dt.getZi()+nrZile <= zileLA[dt.getLuna()])
			return new Data((dt.getZi()+nrZile)+"."+dt.getLuna()+"."+dt.getAn());
		else {
			int z, l, a;
			z=dt.getZi();
			l=dt.getLuna();
			a=dt.getAn();
			while(z+nrZile > zileLA[l]) {
				nrZile -= zileLA[l];
				if(l==12) {
					l=1;
					++a;
				}
				else ++l;
			}
			return new Data((z+nrZile)+"."+l+"."+a);	
		}
	}
	
}
