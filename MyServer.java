import java.io.*;
import java.net.*;

public class MyServer {
	public static void main (String[] args){
		try {
			ServerSocket ss = new ServerSocket(6666);
			Socket s = ss.accept(); //establishes connection
			DataInputStream dis = new DataInputStream(s.getInputStream());

			String  str = (String)dis.readUTF();
			System.out.println("Client's message: " + str);

			String reverse = new StringBuffer(str).reverse().toString();
			System.out.printf("Original message: %s\nReversed message: %s  %n", str, reverse);

			ss.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public static String reverse (String source) {
		if(source == null || source.isEmpty()) {
			return source;
		}

		String reverse = "";
		for(int i = source.length() - 1; i >= 0; i--) {
		    reverse = reverse + source.charAt(i);
		}

		return reverse;
	}
}
