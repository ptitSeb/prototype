#ifndef _FILEIO_H_
#define _FILEIO_H_
//////FILEIO WRAPPER///////
#include <string.h>
#include <stdio.h>

//char* ScanString(char* line, char* string);
class CFileIO
{
private:
	FILE* fPTR;//file pointer
	char m_szFileName[256];//remember the file for re-opening
	char m_szReadMode[12];//read/write mode
	long m_lFileOFFSET;//stored file offset from last read
	char m_szLine[256];//last read line
	
	bool FileOpen()
	{
		if(m_szFileName==NULL)
			return false;
		
		if(!(fPTR=fopen(m_szFileName,m_szReadMode)))
			return false;

		return true;
	}
	bool AppendFile()
	{
		if(m_szFileName==NULL)
			return false;
		if(!(fPTR=fopen(m_szFileName,"a")))
			return false;

		return true;
	}
	bool AppendFileBinary()
	{
		if(m_szFileName==NULL)
			return false;
		if(!(fPTR=fopen(m_szFileName,"ab")))
			return false;

		return true;
	}

public:
	CFileIO()
	{
		fPTR = NULL;
	}
	~CFileIO()
	{}
	void ShutFile()
	{
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);
	}
	//open a file for reading or writing
	bool GetFile(char* filename,char* ReadMode )
	{

		strcpy(m_szFileName,filename);
		strcpy(m_szReadMode,ReadMode);
		
		if(!FileOpen())
			return false;
	
		fseek(fPTR,0,SEEK_SET);
		m_lFileOFFSET=ftell(fPTR);
		fclose(fPTR);

		return true;
	}

	char* ReadLine()
	{
		if(!FileOpen())
			return NULL;//cant open file

		//make sure its not the EOF
		fseek(fPTR,0,SEEK_END);
		if(m_lFileOFFSET==ftell(fPTR))
			return NULL;//end of file

		//move to file offset and get line
		fseek(fPTR,m_lFileOFFSET,SEEK_SET);//move to file offset
		fgets(m_szLine,256,fPTR);//read line from file

		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);

		//close file and return line
		fclose(fPTR);
		return m_szLine;
	}

	char* FindStringInFile(char* string)//returns remaining line
	{
		if(!FileOpen())
			return NULL;//cant open file

		fseek(fPTR,0,SEEK_END);
		long end = ftell(fPTR);
		m_lFileOFFSET=0;
		fseek(fPTR,m_lFileOFFSET,SEEK_SET);//beginning of file
		char* line;
		while(m_lFileOFFSET!=end)
		{
			line = ReadLine();
			if(!line)
				continue;
			char* tok = strtok(line," ");
			if(!strcmp(tok,string))
			{
				m_lFileOFFSET=0;
				tok = strtok(NULL,"\n");
				return tok;
			}
		}
		m_lFileOFFSET=0;
		fclose(fPTR);
		return NULL;
	}

	bool WriteLine(char* txt)
	{
		if(!AppendFile())
			return false;//cant open file

		fwrite(txt,sizeof(char),strlen(txt),fPTR);//write the line
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);

		return true;
	}
#ifdef AMIGAOS4
// generic little->big conversion
template <class T> inline void littleBigEndian (T *x) {
    unsigned char *toConvert = reinterpret_cast<unsigned char *>(x);
	unsigned char tmp;
	const int sz = sizeof(T);
    for (size_t i = 0; i < (sz/2+1); ++i) {
	  tmp = toConvert[i];
      toConvert[i] = toConvert[sz - i - 1];
	  toConvert[sizeof(T) - i - 1] = tmp;
	}
  }
#endif
	template<class T>
	bool WriteBinary(T* data)
	{
		if(!AppendFileBinary())
			return false;//cant open file

#ifdef AMIGAOS4
		if(sizeof(T)>1) {
			T tmp;
			memcpy(&tmp, data, sizeof(tmp));
			littleBigEndian(&tmp);
			fwrite(&tmp,sizeof(T),1,fPTR);//write the line
		} else
#endif
		fwrite(data,sizeof(T),1,fPTR);//write the line
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);

		return true;
	}
	template<class T>
	bool WriteBinary(T* data, int size)
	{
		if(!AppendFileBinary())
			return false;//cant open file

#ifdef AMIGAOS4
		if(sizeof(T)>1) {
			T tmp;
			for(int i=0; i<size; ++i) {
				memcpy(&tmp, data+i, sizeof(tmp));
				littleBigEndian(&tmp);
				fwrite(&tmp,sizeof(T),1,fPTR);//write the line
			}
		} else
#endif
		fwrite(data,sizeof(T),size,fPTR);//write the line
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);

		return true;
	}
	template<class T>
	bool ReadBinary(T* data)
	{
		if(!FileOpen())
			return NULL;//cant open file

		fseek(fPTR,m_lFileOFFSET,SEEK_SET);//move to file offset
		fread(data,sizeof(T),1,fPTR);//write the line
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);
#ifdef AMIGAOS4
		littleBigEndian(data);
#endif

		return true;
	}
	template<class T>
	bool ReadBinary(T* data, int size)
	{
		if(!FileOpen())
			return NULL;//cant open file

		fseek(fPTR,m_lFileOFFSET,SEEK_SET);//move to file offset
		fread(data,sizeof(T),size,fPTR);//write the line
		//get new file OFFSET
		fseek(fPTR,0,SEEK_CUR);
		m_lFileOFFSET = ftell(fPTR);
		//close file and return line
		fclose(fPTR);
#ifdef AMIGAOS4
		for(int i=0; i<size; ++i)
			littleBigEndian(data+i);
#endif

		return true;
	}

	void ReleaseFile()
	{}
};


#endif
