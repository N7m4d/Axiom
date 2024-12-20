#ifndef PCSNODE_H
#define PCSNODE_H

namespace Axiom
{
	class PCSNode
	{
	public:
		// Constants for the library
		static const unsigned int NAME_SIZE = 32;
		static const unsigned int MAJOR_VERSION = 5;
		static const unsigned int MINOR_VERSION = 0;

		// Enums
		enum class Code : uint32_t
		{
			SUCCESS,
			FAIL_NULL_PTR,
			FAIL_RETURN_NOT_INITIALIZED
		};

		// constructor
		PCSNode();

		// copy constructor
		PCSNode(const PCSNode &in);

		// Specialize Constructor
		PCSNode(PCSNode *const pInParent,
				PCSNode *const pInChild,
				PCSNode *const pInNextSibling,
				PCSNode *const pInPrevSibling,
				const char *const pInName);

		PCSNode(const char *const pInName);

		// destructor
		virtual ~PCSNode();

		// assignment operator
		PCSNode &operator = (const PCSNode &in);

		// accessors
		void SetParent(PCSNode *const pIn);
		void SetChild(PCSNode *const pIn);
		void SetNextSibling(PCSNode *const pIn);
		void SetPrevSibling(PCSNode *const pIn);
		void SetForward(PCSNode *const pIn);
		void SetReverse(PCSNode *const pIn);

		PCSNode *GetParent() const;
		PCSNode *GetChild() const;
		PCSNode *GetNextSibling() const;
		PCSNode *GetPrevSibling() const;
		PCSNode *GetForward() const;
		PCSNode *GetReverse() const;

		// name
		Code SetName(const char *const pInName);
		Code GetName(char *const pOutBuffer, unsigned int sizeOutBuffer) const;

		// print
		void PrintNode() const;
		void PrintChildren() const;
		void PrintSiblings() const;

		// get number of children/siblings
		int GetNumSiblings() const;
		int GetNumChildren() const;

	private:
		PCSNode *pParent;
		PCSNode *pChild;
		PCSNode *pNextSibling;
		PCSNode *pPrevSibling;
		PCSNode *pForward;
		PCSNode *pReverse;

		char     pName[NAME_SIZE];
	};

}

#endif
