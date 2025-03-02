#pragma once
#include <set>
#include <string>
#include "IObserver.h"

namespace Arcanoid
{
	class ScoreManager : public IObserver
	{
	public:
		void ClearScore();
		void AddScore(int inc);
		int GetScore();
		std::multiset<int> GetRecordsTable() const;
		void AddEntryToTable();
		void LoadTableFromFile(std::string tablePath);
		void TypeTableToFile(std::string tablePath);
		void Notify(std::shared_ptr<IObservable> observable) override;
	private:
		std::multiset<int> recordsTable;
		int totalScore = 0;
	};
}


