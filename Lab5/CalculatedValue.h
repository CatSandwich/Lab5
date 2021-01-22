#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <string>

template <class T>
class CalculatedValue
{
	public:
	typedef std::function<void(T&)> CalculateFunc;
	typedef std::unordered_map<std::string, CalculateFunc> Layer;

	T Value;

	CalculatedValue() : CalculatedValue{1, T()}
	{

	}

	CalculatedValue(int nLayers, T startingVal)
	{
		std::vector<Layer> temp(nLayers);
		_layers = temp;
		_startingVal = startingVal;
		Calculate();
	}

	CalculatedValue<T>* AddToLayer(unsigned int n, std::string key, CalculateFunc func)
	{
		if (n >= _layers.size())
		{
			throw* (new std::invalid_argument("Writing to layer " + std::to_string(n) + ". Instance has " + std::to_string(_layers.size())));
		}

		Layer tempLayer(_layers[n]);
		std::pair<std::string, CalculateFunc> tempPair(key, func);
		tempLayer.insert(tempPair);
		_layers[n] = tempLayer;

		return this;
	}

	CalculatedValue<T>* WithLayer(unsigned int n, std::string key, CalculateFunc func)
	{
		if (n >= _layers.size())
		{
			throw* (new std::invalid_argument("Writing to layer " + std::to_string(n) + ". Instance has " + std::to_string(_layers.size())));
		}

		Layer tempLayer;
		std::pair<std::string, CalculateFunc> tempPair(key, func);
		tempLayer.insert(tempPair);
		_layers[n] = tempLayer;

		return this;
	}

	T Calculate()
	{
		Value = _startingVal;
		for (unsigned int l = 0; l < _layers.size(); l++)
		{
			for (auto f = _layers[l].begin(); f != _layers[l].end(); f++)
			{
				((*f).second)(Value);
			}
		}
		return Value;
	}

	private:

	T _value;
	T _startingVal;
	std::vector<Layer> _layers;
};