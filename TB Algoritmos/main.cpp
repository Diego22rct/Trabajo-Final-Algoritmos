#include "Registry.hpp"
int main() {
	Registry* Programa = new Registry();
	while (true)
	{
		Programa->iniciarPrograma();
	}
	delete Programa;
	return 0;
}