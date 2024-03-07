#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <iomanip>

//
//  En liten test og demo av tegnsett håndtering.
//  Start programmet via Windows Terminal for best tegnstøtte.
//

void printStringAsHex(const char* navn, const std::string& str, const std::wstring Wstr=L"") {
    std::cout << navn << ": ";

	if (Wstr == L"") {
		for (unsigned char c : str) 
	       std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
    } else {
		for (wchar_t c : Wstr) 
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c) << " ";
	}

    std::cout << std::endl;
}

int main()
{
	// Vindutittel.
	SetConsoleTitleW(L"ÆØÅæøåtest😅");

	//
	// Lokalitet og code page/tegnsett for UTF-8.
	// lokalitet bestemmer hvordan tekst skal tolkes og formateres, 
	// mens tegnsett (code page) bestemmer selve tegnsamlingen som brukes til å oversette binærdata til tegn.
	//
	setlocale(LC_ALL,"en_US.UTF-8"); // Lokalitet er på sett og vis regelsettet som avgjør hvordan tegn skal tolkes.
	SetConsoleOutputCP(CP_UTF8);     // Tegnsett har selve samlingen for oversetting av bytes/binærdata til tegn.

	// Strenger til testing.
	std::string ansi = "æøåÆØÅtest😅";
	std::string utf8 = u8"æøåÆØÅtest😅";
	std::wstring utf16 = L"æøåÆØÅtest😅";

	// Diverse visning.
	std::cout << "ANSI/singlebyte visning med UTF-8 lokalitet burde vise feil: " << ansi << "\n\n";
	std::cout << "UTF-8/multibyte(1-4byte) notasjon med UTF-8 lokalitet burde vise riktig: " << utf8 << "\n\n";
	std::wcout << "UTF-16/wide(2byte) burde vise nesten riktig (ingen emoji): " << utf16 << "\n";
	std::cout << "Emoji viser ikke siden UTF-16 lagring av emoji ikke er den samme som med UTF-8.\n";
	std::cout << u8"æøåÆØÅ virker derimot siden UTF-16 TILFELDIGVIS lagrer det likt som ANSI, se bytes:\n\n";

	// Vis hex verdier.
	printStringAsHex("ANSI", ansi);
	printStringAsHex("UTF-8", utf8);
	printStringAsHex("UTF-16", "", utf16);
	std::cout << "\n";

	// Widechar til Multibyte demo (og evt. andre veien med mbstowcs_s). 
	// Legg merke til hvordan jeg kun trenger å bruke u8"" på strenger som faktisk trenger UTF-8 notasjon.
	size_t i = 0;
	char c[512] = {0};
	wcstombs_s(&i, c, utf16.c_str(), 512);
	std::cout << u8"En widechars konvertering til multibytes funker dersom man velger å bruke std::wstring.\n";
	std::cout << u8"wcstombs_s() virker fint siden UTF-16 fint kan konverteres til UTF-8: " << c << "\n";
	printStringAsHex("", c);
	std::cout << "Nyttig ved forberedelse til funksjoner som forventer std::string eller const char* argument(er).\n\n";

	std::cout << u8"Min egen konklusjon er at std::wstring er mer egnet mot UTF-16 bruk enn UTF-8, selv om det går an.\n"
	             u8"Fra og med C++11 har man u8 notasjon og rimelig bred native UTF-8 støtte i STL (C++ Standard Library).\n\n";

	// Avslutt
	system("pause");
	return 0;
}