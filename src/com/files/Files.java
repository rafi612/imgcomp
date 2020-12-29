package com.files;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.imageio.ImageIO;

public class Files 
{
    public static List<File> listf(String directoryName) 
    {
    	if (!new File(directoryName).isDirectory())
    	{
    		List<File> list = new ArrayList<File>();
    		list.add(new File(directoryName));
    		return list;
    	}
        File directory = new File(directoryName);

        List<File> resultList = new ArrayList<File>();

        // get all the files from a directory
        File[] fList = directory.listFiles();
        resultList.addAll(Arrays.asList(fList));
        
        for (File file : fList) 
        {
            if (file.isFile())
            {
                //System.out.println(file.getAbsolutePath());
            } 
            else if (file.isDirectory()) 
            {
                resultList.addAll(listf(file.getAbsolutePath()));
            }
        }
        return resultList;
    }
    
    public static List<File> listd(List<File> files) 
    {
    	List<File> list = new ArrayList<File>();
    	for (int i = 0;i < files.size();i++)
    	{
    		if (files.get(i).isDirectory())
    			list.add(files.get(i));
    	}
    	return list;
    }
    
    public static List<File> listdfiltred(List<File> files,String foldername,String replace) 
    {
    	List<File> list = new ArrayList<File>();
    	for (int i = 0;i < files.size();i++)
    	{
        	String replaced = files.get(i).getAbsolutePath().replaceAll(foldername, replace);
        	File file = new File(replaced);
    		list.add(file);
    	}
    	return list;
    }
    
    public static void createDirs(List<File> dirs)
    {
    	for (int i = 0;i < dirs.size();i++)
    	{
    		dirs.get(i).mkdirs();
    	}
    }
    
    public static long getDirectorySize(File dir) 
    {

    	if (!dir.isDirectory())
    	{
    		return dir.length();
    	}
    	
        long length = 0;
        File[] files = dir.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isFile())
                    length += file.length();
                else
                    length += getDirectorySize(file);
            }
        }
        return length;

    }
    
    public static String removeExtension(String path)
    {
    	return path.replaceFirst("[.][^.]+$", "");
    }
    
    public static BufferedImage getBufferedImage(File inputfile) throws IOException
    {
    	return ImageIO.read(inputfile);
    }
    
    public static native Image resizen(BufferedImage img, int width,int height,String format);
    
    public static BufferedImage resize(BufferedImage img, int width,int height,String format) 
    {
        Image tmp = img.getScaledInstance(width, height, 1);
        BufferedImage resized;
        if (format.equals("jpg") || format.equals("jpeg"))
        	resized = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        else
        	resized = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = resized.createGraphics();
        g2d.drawImage(tmp, 0, 0, (ImageObserver)null);
        g2d.dispose();
        return resized;
      }
}
