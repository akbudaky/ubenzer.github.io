import java.util.Vector;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author Gergefil
 * @author G�l�g�l
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("K�lyutmaz 1.0");
		System.out.println("Lexical Analyzer and TOPALOGLU++ Languange Parser");
		System.out.println("05-06-7699 Umut BENZER");
		System.out.println("05-06-7670 G�l DEL�ORMAN\n");
		
		String girdi = new String();
		try {
			final BufferedReader in = new BufferedReader(new FileReader("text.txt"));
			String txt = null;
			while ((txt = in.readLine()) != null) {
				girdi = girdi + txt;
			}
			in.close();
		} catch (final IOException e) {
			System.out.println("Er�r: text.txt dosyas� okunamad�. L�tfen bilgisayar�n�z� camdan a�a�� at�n�z! :)");
			System.exit(0);
		}
		
		String one_word= "";
		for(int i = 0; i<girdi.length();i++) { /* Bu k�s�mda sat�r sat�r ayr��t�r�r�z. */
			if(girdi.charAt(i) == ';') {
				System.out.println("\n\nS�radaki komut: " + one_word + ';');
				
				int sayac = 0;
				String temp = "";
				String left = "";
				String right = "";
				boolean cik = false;
				
				for(int x = 0; x<one_word.length();x++) { /* Bir sat�r gezilir ve sa� ve sol de�i�kenlerine ayr��t�r�l�r. */
					if(one_word.charAt(x) == ':' && one_word.length() > x  && one_word.charAt(x+1) == '=') {						
						if (sayac==0) { 
							left = temp;
							/* System.out.println("Sol: " + left + "|"); // Kodun sol k�sm�n� g�rmek i�in commenti kald�r�n. */
							temp = "";
							x++;
						} else { 
							System.out.println("Er�r: Sat�rda birden �ok := atamas� var!");
							cik = true;
							break;
						}
						sayac++;	
					} else {
						temp = temp + one_word.charAt(x);						
					}
				}
				if (cik == true) {one_word = ""; continue; }/* E�er := hatas� varsa daha ne kontrol edeyim ki sat�r�n kalan�n�! */
				right = temp;
				/* System.out.println("Sa�: " + right + "|"); // Kodun sa� k�sm�n� g�rmek i�in commenti kald�r�n� */
				
				if (!is_variable(left)) {
					System.out.println("Er�r: Sol taraf de�i�keni hatal�!"); 
					one_word = ""; 
					continue; 
				}
				System.out.println("symbol (':=')");				
				is_operation(right);
				one_word = "";
			} else {
				one_word = one_word + girdi.charAt(i);
			}
		}
		if (one_word.trim() != "") System.out.println("Er�r: Kodun en sonunda fazlal�k var.");
	}
	
	/**
	 * G�nderilen Stringin ge�erli bir variable olup olmad���n� bulur
	 * @param suspect
	 * @return boolean
	 */
	public static boolean is_variable(String suspect) {	
		suspect = suspect.trim();		
		for (int e = 0; e < suspect.length(); e++) {
			if (!is_character(suspect.charAt(e))) return false;
		}
		System.out.println("variable ('" + suspect + "')"); 
		return true;
	}
	
	/**
	 * G�nderilen stringin ge�erli bir sa� taraf i�lemi olup olmad���n� bulur.
	 * @param data
	 * @return boolean
	 */
	public static boolean is_operation(String data) {
		
		int index = 0;
		int parantez = 0;
		Vector<String> expected = new Vector<String>();
		
		expected.add("char");
		expected.add("space");
		expected.add("-number");
		expected.add("*");
		expected.add("number");
		expected.add("parantez-ac");

		while (1==1) {
			if (index == data.length()) {
				if (parantez != 0) { System.out.println("Er�r: A��k kalan parantez var."); return false; }
				if (!expected.contains("finish")) { System.out.println("Er�r: Komut sonu beklenmiyordu."); return false; }
				System.out.println("symbol (';')"); 
				return true;				
			}
			if (data.charAt(index) == '(' && expected.contains("parantez-ac")) {
				System.out.println("symbol ('(')"); 
				
				parantez++;
				index++;
				expected.clear();
				expected.add("char");
				expected.add("space");
				expected.add("-number");
				expected.add("number");
				expected.add("parantez-ac");
				continue;
			} else if (data.charAt(index) == ')' && expected.contains("parantez-kapa")) {
				parantez--;
				index++;
				if (parantez < 0) { System.out.println("Er�r: Parantezler gere�inden fazla kapanm��."); return false; }
				System.out.println("symbol (')')"); 
				
				expected.clear();
				expected.add("char");
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("number");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;
			} else if (is_numeric(data.charAt(index)) && expected.contains("number")) {
				String sayi = "";
				do {
					sayi = sayi + data.charAt(index);
					index++;					
				} while(index < data.length() && is_numeric(data.charAt(index)));
				
				System.out.println("intConstant ('" + sayi + "')"); 
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;
			} else if ((data.charAt(index) == '-') && expected.contains("-number")) {
				String sayi = "-";
				boolean once = false;
				index++;
				while(index < data.length() && is_numeric(data.charAt(index))) {
					once = true;
					sayi = sayi + data.charAt(index);
					index++;
				}
				
				if (!once) { System.out.println("Er�r: - beklenmiyordu."); return false; }
				System.out.println("intConstant ('" + sayi + "')");
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;	
			} else if (is_character(data.charAt(index)) && expected.contains("char")) {
				String karakter = "";
				do {
					karakter = karakter + data.charAt(index);
					index++;					
				} while(index < data.length() && is_character(data.charAt(index)));
				
				System.out.println("variable ('" + karakter + "')");
				
				expected.clear();
				expected.add("space");
				expected.add("-");
				expected.add("*");
				expected.add("parantez-kapa");
				expected.add("finish");
				continue;				
			} else if ((data.charAt(index) == '-') && expected.contains("-")) {
				System.out.println("symbol ('-')"); 
				index++;

				expected.clear();
				expected.add("space");
				expected.add("number");
				expected.add("char");
				expected.add("parantez-ac");
				continue;
				/* - de�i�ken kabul oluyor �u notkada. */
			} else if ((data.charAt(index) == '+' || data.charAt(index) == '*') && expected.contains("*")) {
				System.out.println("symbol ('" + data.charAt(index) + "')"); 
				
				index++;
				expected.clear();
				expected.add("space");
				expected.add("number");
				expected.add("char");
				expected.add("parantez-ac");
				continue;
			} else if (data.charAt(index) == ' ' && expected.contains("space")) {
				index++;
				continue;
			} else {
				System.out.println("Er�r: Sa� tarafta beklenmeyen karakter. Beklenenler: " + expected.toString()); 
				return false;
			}
		}
	}

	/**
	 * G�nderilen karakterin rakam olup olmad���n� bulur.
	 * @param in
	 * @return boolean
	 */
	public static boolean is_numeric(char in) {
		if (!(in =='1'||in=='2'||in=='3'||in=='4'||in=='5'||in=='6'||in=='7'||in=='8'||in=='9'||in=='0')) return false;
		return true;
	}
	
	/**
	 * G�nderilen karakterin ge�erli bir de�i�ken ismi olu�turacak karakter olup olmad���n� d�nd�r�r. 
	 * @example (misal _ A B ge�erli ama ? ! 2 ge�erli de�il.)
	 * @param in
	 * @return boolean
	 */
	public static boolean is_character(char in) {
		if (!(in =='A'||in=='B'||in=='C'||in=='D'||in=='E'||in=='F'||in=='G'||in=='�'||in=='H'||in=='I'||in=='�'||in=='J'||in=='K'||in=='L'||in=='M'
			||in=='N'||in=='O'||in=='�'||in=='P'||in=='R'||in=='S'||in=='�'||in=='T'||in=='U'||in=='�'||in=='V'||in=='Y'||in=='Z'||
			
			in =='a'||in=='b'||in=='c'||in=='d'||in=='e'||in=='f'||in=='g'||in=='�'||in=='h'||in=='�'||in=='i'||in=='j'||in=='k'||in=='l'||in=='m'
			||in=='n'||in=='o'||in=='�'||in=='p'||in=='r'||in=='s'||in=='�'||in=='t'||in=='u'||in=='�'||in=='v'||in=='y'||in=='z'||in=='_'		
		)) return false;
		return true;
	}
}