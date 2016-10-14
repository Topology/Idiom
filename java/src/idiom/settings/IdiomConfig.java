package idiom.settings;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import idiom.IdiomUtility;

public class IdiomConfig {
	InputStream langdef;
	InputStream langinst;

	public IdiomConfig(String[] args) {
		if(args.length > 1)
			try {
				langdef = new FileInputStream(new File(args[1]));
			} catch (FileNotFoundException e) {
				IdiomUtility.FatalError(e, "First commandline argument must be the path to the language definition.");		
			}
		else
			langdef = System.in;
		if(args.length > 2)
			try {
				langinst = new FileInputStream(new File(args[2]));
			} catch (FileNotFoundException e) {
				IdiomUtility.FatalError(e, "Second commandline argument must be the path to the language instance.");		
			}
		else
			langinst = System.in;
	}

	
	public InputStream getLanguageDefinition(){
		return null;
		
	}
	
	public InputStream getLanguageInstance(){
		return null;
	}
	
	
}
