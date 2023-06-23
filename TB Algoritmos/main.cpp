#include "Registry.hpp"
int main() {
	Registry* Programa = new Registry();
	bool run = true;
	while (run)
	{
		run = Programa->iniciarPrograma();
	}
	delete Programa;
	return 0;
}