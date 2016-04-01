import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		BigInteger a[] = new BigInteger[4];
		a[0] = cin.nextBigInteger();
		a[1] = cin.nextBigInteger();
		a[2] = cin.nextBigInteger();
		boolean flag = false;
		for (int i = 0; i < 3; ++ i) {
			for (int j = 0; j < 3; ++ j) {
				for (int t = 0; t < 3; ++ t) {
					BigInteger tmp = a[i].add(a[j]);
					if (tmp.equals(a[t])) {
						flag = true;
					}
				}
			}
		}
		if (flag) {
			System.out.println("YES");
		}
		else {
			System.out.println("NO");
		}
		cin.close();

	}

}
