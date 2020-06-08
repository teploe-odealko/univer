//////////////////////////////////////////////////////////////////////////////////////////
//	ARB_program.cpp
//	functions for an ARB program (vertex, fragment etc)
//	Downloaded from: www.paulsprojects.net
//	Created:	2nd October 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>
#include "glee.h"			//header for OpenGL 1.4
#include "../Log/LOG.h"
#include "ARB_program.h"

bool LoadARB_program(GLenum target, char * filename)
{
	//Open file
	std::ifstream vpFile(filename, std::ios::in | std::ios::binary);
	if(vpFile.fail())
	{
		printf("Unable to open vertex program\n");
		return false;
	}

	//calculate the size of the file
	vpFile.seekg(0, std::ios::end);
	int vpSize=vpFile.tellg();
	vpFile.seekg(0, std::ios::beg);
	
	//allocate memory
	unsigned char * vpText=new unsigned char[vpSize];
	if(!vpText)
	{
		printf("Unable to allocate space for vertex program text\n");
		return false;
	}

	//read file
	vpFile.read(reinterpret_cast<char *>(vpText), vpSize);
	vpFile.close();

	//Send program string to OpenGL
	glProgramStringARB(target, GL_PROGRAM_FORMAT_ASCII_ARB, vpSize, vpText);
	
	if(vpText)
		delete [] vpText;
	vpText=NULL;

	//Output error/warning messages
	const GLubyte * programErrorString=glGetString(GL_PROGRAM_ERROR_STRING_ARB);
	
	//Output position if there was an error
	int errorPos;
	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);
	if(errorPos!=-1)
	{
		LOG::Instance()->OutputError("Program error at position %d in %s", errorPos, filename);
		LOG::Instance()->OutputError("Error String:\n%s", programErrorString);
		return false;
	}

	return true;
}