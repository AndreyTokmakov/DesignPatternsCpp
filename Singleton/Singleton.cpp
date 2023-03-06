
#include "Singleton.h"

#include <fstream>
#include <deque>


namespace Singleton {

	Singleton* Singleton::Singleton::instance = nullptr;

	Singleton::Singleton() {
		this->counter = 0;
		std::cout << "Singleton::Singleton()" << std::endl;
	}

	Singleton* Singleton::Instance() {
		if (nullptr == instance) {
			instance = new Singleton();
		}
		return instance;
	}
}

namespace Singleton::SharedPtrSingleton {

	SingletonSharedPtr::SingletonSharedPtr() {
		this->counter = 0;
		std::cout << "SingletonSharedPtr::SingletonSharedPtr()" << std::endl;
	}

	std::shared_ptr<SingletonSharedPtr> SingletonSharedPtr::Instance() {
		struct make_shared_enabler : public SingletonSharedPtr {};
		static std::shared_ptr<make_shared_enabler> instance = std::make_shared<make_shared_enabler>();
		return instance;
	}

	///////////////////////////////////////////
	
	void Test() {
		std::shared_ptr<SingletonSharedPtr> s1 = SingletonSharedPtr::Instance();
		std::shared_ptr<SingletonSharedPtr> s2 = SingletonSharedPtr::Instance();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s2->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;
	}
}

namespace Singleton::SingletonTests {

	void Test1() {
		Singleton* s1 = Singleton::Instance();
		Singleton* s2 = Singleton::Instance();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s2->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

	}

	void Singleton_SharedPtr() {
		Singleton* s1 = Singleton::Instance();
		Singleton* s2 = Singleton::Instance();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s2->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

		s1->Increment();

		std::cout << s1->GetCounter() << std::endl;
		std::cout << s2->GetCounter() << std::endl;

	}
}

////////////////////////////////////////////////////////////////////////////////////


namespace Singleton::MeyersSingleton {

	class MSingleton {
	protected:
		long counter{0};

	public:
		static MSingleton* Instance();

	public:
		inline void Increment() noexcept {
			this->counter++;
		}

		[[nodiscard]]
        inline long GetCounter() const noexcept {
			return this->counter;
		}

	private:
		MSingleton() {
			std::cout << "MSingleton::MSingleton()" << std::endl;
		};

		~MSingleton() {
			std::cout << "MSingleton::~MSingleton()" << std::endl;
		};

	public:
		MSingleton(const MSingleton& obj) = delete;
		MSingleton(MSingleton&& obj) noexcept = delete;
		MSingleton& operator=(const MSingleton& obj) = delete;
		MSingleton& operator=(MSingleton&& obj) noexcept = delete;
	};

	MSingleton* MSingleton::Instance() {
		static MSingleton theSingleInstance;
		return &theSingleInstance;
	}


	///////////////////// BAD ////////////////////////////////////


	MSingletonBad& MSingletonBad::Instance() {
		static MSingletonBad theSingleInstance;
		return theSingleInstance;
	}

	MSingletonBad::MSingletonBad() {
		std::cout << "MSingletonBad::MSingletonBad()" << std::endl;
	};

}

/////////////////////////////////////////

namespace Singleton::MeyersSingletonTests {

	using namespace MeyersSingleton;

	void Test1() {
		MSingleton* s1 = MSingleton::Instance();
		MSingleton* s2 = MSingleton::Instance();

		s1->Increment();
		std::cout << s2->GetCounter() << std::endl;
		s2->Increment();
		std::cout << s1->GetCounter() << std::endl;
	}

	void Test2() {
		MSingleton::Instance()->Increment();
		std::cout << MSingleton::Instance()->GetCounter() << std::endl;
		MSingleton::Instance()->Increment();
		std::cout << MSingleton::Instance()->GetCounter() << std::endl;
	}

	void TestBad() {
		MSingletonBad& s1 = MSingletonBad::Instance();
		MSingletonBad& s2 = MSingletonBad::Instance();

		std::cout << s1.GetCounter() << std::endl;
		std::cout << s2.GetCounter() << std::endl;

		s1.Increment();

		std::cout << s1.GetCounter() << std::endl;
		std::cout << s2.GetCounter() << std::endl;

		s1.Increment();

		std::cout << s1.GetCounter() << std::endl;
		std::cout << s2.GetCounter() << std::endl;
	}
}


namespace Singleton::MeyersSingleton_LifeTimeTests {

	class MSingleton {
	protected:
		long counter{ 0 };
		std::fstream log_File;

	public:
		static MSingleton* Instance();

	public:
		inline void Increment() noexcept {
			this->counter++;
		}

		inline long GetCounter() const noexcept {
			return this->counter;
		}

	private:
		MSingleton() {
			log_File.open(R"(C:\Temp\trace.log)", std::ios::out);

			log_File << "MSingleton::MSingleton()\n";
		};

	public:
		MSingleton(const MSingleton& obj) = delete;
		MSingleton(MSingleton&& obj) noexcept = delete;
		MSingleton& operator=(const MSingleton& obj) = delete;
		MSingleton& operator=(MSingleton&& obj) noexcept = delete;

		~MSingleton() {
			log_File << "MSingleton::~MSingleton()\n";
		};
	};

	MSingleton* MSingleton::Instance() {
		static MSingleton theSingleInstance;
		return &theSingleInstance;
	}

	//======================================================================//

	void Test() {
		MSingleton* obj = MSingleton::Instance();
		obj->Increment();

		std::cout << obj->GetCounter() << std::endl;
		// delete obj;
	}
}

namespace Singleton::FileRepository
{

    class FileRepository
    {
    private:
        std::deque<std::string> files;

        FileRepository() {
            std::cerr << " [LOG] File Repository Initialized." << "\n";
        }

    public:

        FileRepository(const FileRepository&) = delete;
        FileRepository& operator=(const FileRepository&) = delete;

        ~FileRepository(){
            std::cerr << " [LOG] File Repository Deleted. Ok." << "\n";
        }

        // Return a reference to not allow client code to delete object.
        static FileRepository& getInstance() {
            static auto instance = std::unique_ptr<FileRepository>{nullptr};
            if(!instance) /** Initialized once - lazy initialization **/
                instance.reset(new FileRepository);
            return *instance;
        }

        void addFile(std::string filename) noexcept{
            files.push_back(std::move(filename));
        }

        void clearFiles() noexcept {
            files.clear();
        }

        void showFiles() const noexcept {
            for (const auto& file: files)
                std::cout << " File = " << file << std::endl;
        }
    };

    // ----------------------------------

    void Test()
    {
        FileRepository& repo1 = FileRepository::getInstance();
        repo1.addFile("CashFlowStatement.txt");
        repo1.addFile("Balance-Sheet.dat");
        repo1.addFile("Sales-Report.csv");

        FileRepository& repo2 = FileRepository::getInstance();

        std::cout << std::boolalpha << "Same object? (&repo == &repo1 ?) = " << (&repo1 == &repo2) << std::endl;

        std::cout << "\nRepository files" << std::endl;
        repo2.showFiles();

        std::cout << "\nAdd more files" << std::endl;
        repo2.addFile("fileX1.pdf");
        repo2.addFile("fileX2.pdf");
        repo2.addFile("fileX3.pdf");
        repo2.showFiles();
    }
};



void Singleton::TEST_ALL()
{
	// MeyersSingletonTests::Test1();
	// MeyersSingletonTests::TestBad();

	// MeyersSingleton_LifeTimeTests::Test();

	// SingletonTests::Test1();

	// SharedPtrSingleton::Test();

    FileRepository::Test();
}
