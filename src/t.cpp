template<class T, int... X> T pi(T{X...});

int main() {
	return pi<int, 42>;
}
