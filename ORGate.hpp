#ifndef ORGATE_HPP
#define ORGATE_HPP

#include "SynchrotronComponent.hpp"
#include "Exceptions.hpp"
using namespace Synchrotron;

namespace CPUComponents {

	/** \brief	**ORGate** : OR all inputs together.
	 *
	 *	\param	bit_width
	 *		This template argument specifies the width of the in and output connections.
	 */
	template <size_t bit_width>
	class ORGate : public SynchrotronComponent<bit_width> {
		public:
			/**
			 *	Default constructor
			 */
			ORGate(size_t initial_value = 0) : SynchrotronComponent<bit_width>(initial_value) {}

			/**	Copy constructor
			 *	\param	Other
			 *		SynchrotronComponent to copy from
			 *	\param	duplicateAll_IO
			 *		Specifies whether to only copy inputs (false) or outputs as well (true).
			 */
			ORGate(const SynchrotronComponent<bit_width>& other, bool duplicateAll_IO = false)
				: SynchrotronComponent<bit_width>(other, duplicateAll_IO) {}

			/**
			 *	Default destructor
			 */
			~ORGate() {}

			/**	\brief	The tick() method will be called when one of this Gate's inputs issues an emit().
			 *
			 *	\exception	Exceptions::Exception
			 *		Throws exception if less than 2 inputs are connected (undefined behaviour).
			 */
			inline void tick() {
				#ifdef THROW_EXCEPTIONS
					if (this->getIputs().size() < 2)
						throw Exceptions::Exception("[ERROR] ORGate requires at least 2 inputs!");
				#endif
				std::bitset<bit_width> prevState = this->state;

				this->state.reset();	// Default non-destructive state for OR-operation

				for(auto& connection : this->getIputs()) {
					this->state |= connection->getState();
				}

				if (prevState != this->state) this->emit();
			}
	};
}

#endif // ORGATE_HPP