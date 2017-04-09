import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class Test {
	public static void main (String[] args) throws Exception {
		try {
			InputStream in = new FileInputStream("/home/liyakamilia/Desktop/input.txt");
			StringBuilder sb = new StringBuilder();
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String read;

			while((read = br.readLine()) != null) {
				sb.append(read);
			}

			BufferedWriter out = null;

			try {
				FileWriter fstream = new FileWriter("/home/liyakamilia/Desktop/test.bin", true);
				out = new BufferedWriter(fstream);

				String str = sb.toString();
				String result = "";

				char[] messChar = str.toCharArray();
				out.newLine();

				for(int i = messChar.length - 1; i >= 0; i--) {
					result = Integer.toBinaryString(messChar[i]);
					if(result.length() < 8)
						out.write(messChar[i] + "(00" + Integer.toBinaryString(messChar[i]) + ") ");
					else
						out.write(messChar[i] + "(" + Integer.toBinaryString(messChar[i]) + ") ");
				}
				br.close();
			}
			catch (IOException e) {
				System.err.println("Error: " + e.getMessage());
			}

			finally {
				if(out != null)
					out.close();
			}
		}
		catch (IOException e) {
			System.out.println("File Read Error");
		}
	}
}
