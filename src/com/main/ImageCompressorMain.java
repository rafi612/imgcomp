package com.main;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.imageio.ImageIO;

import com.files.Files;

public class ImageCompressorMain 
{

	public static void main(String[] args) 
	{
		if (args.length < 1) 
		{
			help();
			System.exit(0);
		}
		else
		{
			int move;
			Args.flags = args[0];
			if (args.length > 1) 
			{
			
				if (args[0].startsWith("-")) move = 0;
				else move = 1;
				
				Args.directory = args[1 - move];
				Args.divider = Double.parseDouble(args[2 - move]);
				Args.format = args[3 - move];
				
				if (Args.divider == 0) Args.divider = 1;
			}
			
			if(Args.flags.contains("k"))
				Args.keepfiles = true;
			
			if(Args.flags.contains("n"))
				Args.names = true;
			
			if(Args.flags.startsWith("-help"))
				help();
			
		}
		compress();
	}
	
	public static void compress()
	{
		System.out.println("Searching files...");
		List<File> files = Files.listf(Args.directory);
		
		
		long sizebefore = Files.getDirectorySize(new File(Args.directory));
		System.out.println(files.size() + " files found in all directories and subdirectories");
		System.out.println("Size total:" + (sizebefore / 1000 / 1000) + "MB (" + sizebefore + " Bytes)");
		
		
		if (Args.keepfiles) 
		{
			System.out.println("Copying original files...");
			Files.copyFolder(new File(Args.directory), new File(Args.directory + "-original"));
		}
		
		int percent;
		
		String filenameaddon = "-compress.";
		if (Args.names) filenameaddon = ".";
		
		for (int i = 0; i < files.size();i++)
		{
			percent = (int)((double)i / (double)files.size() * (double)100);
		    if (!files.get(i).isDirectory())
		    	try 
		    {
		    	System.out.println("Compressed: " + percent  + "%");
			    System.out.println("Compressing " + files.get(i).getName() + "...");
			    BufferedImage image = Files.getBufferedImage(files.get(i));
			    
			    BufferedImage resized = Files.resize(image,(int)(image.getWidth() / Args.divider),(int)( image.getHeight() / Args.divider),Args.format);
			    
			    String parent = files.get(i).getParent() + File.separator;
			    if (parent.equals("null" + File.separator)) parent = "";
			    
			    File output = new File(Files.removeExtension(parent + files.get(i).getName()) + filenameaddon + Args.format);
			    files.get(i).delete();
			    
			    ImageIO.write(resized, Args.format, output);
			    System.out.println("Compressing: " + files.get(i).getName() + " complete!!!");
			    System.out.println("Output file: " + output.getName() + "\n");
		    } 
		    catch (Exception e) 
		    {
		    	System.out.println("File:" + files.get(i) + " is not image \n");
		    }
		}
		
		System.out.println("Compression Complete!!!");
		System.out.println("Searching files...\n");
		long sizeafter = Files.getDirectorySize(new File(Args.directory));
		
		System.out.println("Size before:" + (sizebefore / 1000 / 1000) + "MB (" + sizebefore + " Bytes)");
		System.out.println("Size after:" + (sizeafter / 1000 / 1000) + "MB (" + sizeafter + " Bytes)");
		
		double ratio = (int)((double)sizeafter / (double)sizebefore * (double)100);
		System.out.println("Lossy compression ratio: " + ratio + "%");
	}

	private static void help() 
	{
		System.out.println("Usage: imgcomp -<flags> <folder or image path> <divider> <format>");
		System.out.println("Flags: -k - keep original files");
		System.out.println("Flags: -n - keep original names on compressed files");
		System.out.println("Flags: -help - shows how to use imgcomp");
		System.out.println("Flags use: -xyz");
		System.out.println("If you dont use flags use: imgcomp <folder or image path> <divider> <format>");
		System.out.println("Divider: Resolution was divided by divider");
		System.out.println("Format: png/jpg/gif etc.. (jpg recomended)");
		System.exit(0);
	} 

}
