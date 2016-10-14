package idiom;


public abstract class IdiomUtility {
	
	static public void FatalError(Exception e, String msg){
		if(e != null)
		 e.printStackTrace();
		System.err.println(msg);
		System.exit(-1);
	}

}
