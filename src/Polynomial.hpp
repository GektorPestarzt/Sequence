template<class T>
class Polynomial
{
private:
	class Monom
	{
	public:
		int pow;
		T factor;

	public:
		Monom(const T& _factor, int _pow) : pow(_pow), factor(_factor) {}
	};
	
private:
	ArraySequence<Monom*>* pol{nullptr};

public:
	Polynomial() : pol(new ArraySequence<Monom*>) {};

	Polynomial(const T& _factor, int _pow)
	{
		Monom* a = new Monom(_factor, _pow);
		this->pol->Push(a);
	}

public:
	void Add(const T& _factor, int _pow)
	{
		if (this->pol == nullptr)
		{
			Monom* a = new Monom(_factor, _pow);
			this->pol->Push(a);

			return;
		}

		for (int i = 0; i < pol->GetLength(); i++)
		{
			if (this->pol->Get(i)->pow == _pow)
			{
				(*this->pol)[i]->factor += _factor;
				return;
			}
		}

		Monom* a = new Monom(_factor, _pow);
		this->pol->Push(a);
	}

	void Subtract(const T& _factor, int _pow)
	{
		Add(-_factor, _pow);
	}

	void MultByScalar(const T& scalar)
	{
		if (scalar == 0)
		{
			delete this;
			return;
		}

		for (int i = 0; i < this->pol->GetLength(); i++)
		{
			(*this->pol)[i]->factor *= scalar;
		}
	}

	Polynomial* Mult(const Polynomial& data)
	{
		Polynomial* newOne = new Polynomial();

		for (int i = 0; i < this->pol->GetLength(); i++)
			for (int j = 0; j < data.pol->GetLength(); j++)
				newOne->Add((*this->pol)[i]->factor * (*data.pol)[j]->factor, (*this->pol)[i]->pow + (*data.pol)[j]->pow);

		return newOne;
	}

	Polynomial* Compos(const Polynomial& data)
	{
		Polynomial* newOne;

		for (int i = 0; i < this->pol->GetLength(); i++)
			for (int j = 0; j < data.pol->GetLength(); j++)
				newOne->Add((*this->pol)[i]->factor * (*data.pol)[j]->factor * (*this->pol)[i]->pow, (*this->pol)[i]->pow * (*data.pol)[j]->pow);

		return newOne;
	}

	T Solve(const T& item)
	{
		T answer = 0;

		for (int i = 0; i < this->pol->GetLength(); i++)
			answer += (*this->pol)[i]->factor * pow(item, (*this->pol)[i]->pow);

		return answer;
	}
};
