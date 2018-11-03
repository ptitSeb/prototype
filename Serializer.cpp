#include "Serializer.h"
#define PRINT_SERIAL
//================================================================================================//
						/**************************************************
						** Serializer:	Will read/write config variables **	
						***************************************************/
//================================================================================================//
Serializer gSerializer;

//================================================================================================//
						/********************************************************
						** Comments are only written if the file did not exist **	
						*********************************************************/
//================================================================================================//
void Serializer::PutComment(string file, string comment)
{
	if(SearchFileGenerate(file))
	{
		ofstream f;
		f.open(file.c_str(),ios::app);
		f << comment << endl;
		f.close();
	}
}
//================================================================================================//
						/************************************************************************************
						** Read variable will search the file for variable and load it into the parsed var **
						** If the file did not exist, it will be written instead (auto-generation)         **
						*************************************************************************************/
//================================================================================================//
void Serializer::ReadVariable(string file, string varname, int& value)
{
	if(SearchFileGenerate(file))//need to write to the cfg
	{
		ofstream f;
		f.open(file.c_str(),ios::app);
		f << varname << "	= " << value << endl;
		f.close();
	}
	else//need to read from the config
	{
		ifstream f;
		f.open(file.c_str());
		string s;
		while(!f.eof())
		{
			getline(f,s);
			string tok;
			string tok2;
			size_t p = s.find('=');
			if(p!=string::npos) {
				tok = s.substr(0, p);
				tok2 = s.substr(p+1, string::npos);
				//trim tok (there must be better way to do that...)
				while(tok.size() && tok[0]==' ')
					tok.erase(0, 1);
				if(tok.find(' ')!=string::npos)
					tok.erase(tok.find(' '), string::npos);
				if(tok.find('\t')!=string::npos)
					tok.erase(tok.find('\t'), string::npos);
			}
//			stringstream(s) >> tok;
			if(tok == varname)
			{
//				stringstream(s) >> tok >> tok2 >> value;
				while(tok2.size() && tok2[0]==' ')
					tok2.erase(0, 1);
				if(tok2.find(' ')!=string::npos)
					tok2.erase(tok2.find(' '), string::npos);
				if(tok2.find('\t')!=string::npos)
					tok2.erase(tok2.find('\t'), string::npos);
				int tmp;
				if(sscanf(tok2.c_str(), "%d", &tmp)==1)
					value = tmp;
#ifdef PRINT_SERIAL
					printf("%s read from file %s\n",tok.c_str(),file.c_str());
#endif
				break;
			}
#ifdef PRINT_SERIAL
			if(f.eof())
			{
				printf("Failed to read %s from file %s\n",varname.c_str(),file.c_str());
			}
#endif
		}
		f.close();
	}
}
void Serializer::ReadVariable(string file, string varname, float& value)
{
	if(SearchFileGenerate(file))
	{
		ofstream f;
		f.open(file.c_str(),ios::app);
		f << varname << "	= " << value << endl;
		f.close();
	}
	else//need to read from the config
	{
		ifstream f;
		f.open(file.c_str());
		string s;
		while(!f.eof())
		{
			getline(f,s);
			string tok;
			string tok2;
			size_t p = s.find('=');
			if(p!=string::npos) {
				tok = s.substr(0, p);
				tok2 = s.substr(p+1, string::npos);
				//trim tok
				while(tok.size() && tok[0]==' ')
					tok.erase(0, 1);
				if(tok.find(' ')!=string::npos)
					tok.erase(tok.find(' '), string::npos);
				if(tok.find('\t')!=string::npos)
					tok.erase(tok.find('\t'), string::npos);
			}
			if(tok == varname)
			{
//				stringstream(s) >> tok >> tok2 >> value;
				while(tok2.size() && tok2[0]==' ')
					tok2.erase(0, 1);
				if(tok2.find(' ')!=string::npos)
					tok2.erase(tok2.find(' '), string::npos);
				if(tok2.find('\t')!=string::npos)
					tok2.erase(tok2.find('\t'), string::npos);
				float tmp;
				if(sscanf(tok2.c_str(), "%f", &tmp)==1)
				value = tmp;
#ifdef PRINT_SERIAL
				printf("%s read from file %s\n",tok.c_str(),file.c_str());
#endif
				break;
			}
#ifdef PRINT_SERIAL
			if(f.eof())
			{
				printf("Failed to read %s from file %s\n",varname.c_str(),file.c_str());
			}
#endif
		}
		f.close();
	}
}
void Serializer::ReadVariable(string file, string varname, string& value)
{
	if(SearchFileGenerate(file))
	{
		ofstream f;
		f.open(file.c_str(),ios::app);
		f << varname << "	= " << value << endl;
		f.close();
	}
	else//need to read from the config
	{
		ifstream f;
		f.open(file.c_str());
		string s;
		value.clear();
		while(!f.eof())
		{
			getline(f,s);
			string tok;
//			stringstream(s) >> tok;
			if(tok == varname)
			{
				string tok2;
//				stringstream(s) >> tok >> tok2 >> value;
#ifdef PRINT_SERIAL
				printf("%s read from file %s\n",tok.c_str(),file.c_str());
#endif
				break;
			}
#ifdef PRINT_SERIAL
			if(f.eof())
			{
				printf("Failed to read %s from file %s\n",varname.c_str(),file.c_str());
			}
#endif
		}
		f.close();
	}
}
//================================================================================================//
						/************************************************************************
						** Search through the gen file list, see if this file needs generating **	
						*************************************************************************/
//================================================================================================//
bool Serializer::SearchFileGenerate(string file)
{
	ifstream f;
	f.open(file.c_str());
	if(!f.is_open())//if the file doesnt exit, then it really need to be generated
	{
		m_GenFiles.push_back(file);
#ifdef PRINT_SERIAL
		printf("file %s will be generated...\n",file.c_str());
#endif
		return true;
	}
	f.close();

	//ok it does exist allredy, but we might still need to continue generation
	vector<string>::iterator i;
	for(i=m_GenFiles.begin(); i<m_GenFiles.end(); i++)
	{
		if(file == (*i))
			return true;//uh oh, need to write out
	}
	return false;//safe to read in
}