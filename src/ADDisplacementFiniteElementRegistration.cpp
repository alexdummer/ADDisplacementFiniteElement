#include "Marmot/ADDisplacementFiniteElement.h"
#include "Marmot/Marmot.h"
#include "Marmot/MarmotFiniteElement.h"
#include "Marmot/MarmotFiniteElementSpatialWrapper.h"

namespace Marmot::Elements::Registration {

  template < class T,
             Marmot::FiniteElement::Quadrature::IntegrationTypes integrationType,
             typename T::SectionType                             sectionType >
  MarmotLibrary::MarmotElementFactory::elementFactoryFunction makeFactoryFunction()
  {
    return []( int elementID ) -> MarmotElement* { return new T( elementID, integrationType, sectionType ); };
  }

  using namespace MarmotLibrary;
  using namespace Marmot::FiniteElement::Quadrature;

  const static bool ADCPS4_isRegistered = MarmotElementFactory::
    registerElement( "ADCPS4",
                     MarmotLibrary::ElementCode::ADCPS4,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 4 >,
                                          FullIntegration,
                                          ADDisplacementFiniteElement< 2, 4 >::PlaneStress >() );

  const static bool ADCPE4_isRegistered = MarmotElementFactory::
    registerElement( "ADCPE4",
                     MarmotLibrary::ElementCode::ADCPE4,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 4 >,
                                          FullIntegration,
                                          ADDisplacementFiniteElement< 2, 4 >::PlaneStrain >() );

  const static bool ADCPS8R_isRegistered = MarmotElementFactory::
    registerElement( "ADCPS8R",
                     MarmotLibrary::ElementCode::ADCPS8R,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 8 >,
                                          ReducedIntegration,
                                          ADDisplacementFiniteElement< 2, 8 >::PlaneStress >() );

  const static bool ADCPE8R_isRegistered = MarmotElementFactory::
    registerElement( "ADCPE8R",
                     MarmotLibrary::ElementCode::ADCPE8R,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 8 >,
                                          ReducedIntegration,
                                          ADDisplacementFiniteElement< 2, 8 >::PlaneStrain >() );

  const static bool ADC3D8_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D8", MarmotLibrary::ElementCode::ADC3D8, []( int elementID ) -> MarmotElement* {
      return new ADDisplacementFiniteElement< 3,
                                              8 >( elementID,
                                                   Marmot::FiniteElement::Quadrature::IntegrationTypes::FullIntegration,
                                                   ADDisplacementFiniteElement< 3, 8 >::SectionType::Solid );
    } );

  const static bool ADC3D20_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D20", MarmotLibrary::ElementCode::ADC3D20, []( int elementID ) -> MarmotElement* {
      return new ADDisplacementFiniteElement< 3, 20 >( elementID,
                                                       Marmot::FiniteElement::Quadrature::IntegrationTypes::
                                                         FullIntegration,
                                                       ADDisplacementFiniteElement< 3, 20 >::SectionType::Solid );
    } );

  const static bool ADC3D20R_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D20R", MarmotLibrary::ElementCode::ADC3D20R, []( int elementID ) -> MarmotElement* {
      return new ADDisplacementFiniteElement< 3, 20 >( elementID,
                                                       Marmot::FiniteElement::Quadrature::IntegrationTypes::
                                                         ReducedIntegration,
                                                       ADDisplacementFiniteElement< 3, 20 >::SectionType::Solid );
    } );
  /*
  MarmotElement* generateT2D2( int elementID )
  {
    auto uelT2D2 = std::unique_ptr< MarmotElement >(
      new ADDisplacementFiniteElement< 1, 2 >( elementID,
                                             Marmot::FiniteElement::Quadrature::IntegrationTypes::FullIntegration,
                                             ADDisplacementFiniteElement< 1, 2 >::SectionType::UniaxialStress ) );
    constexpr static int indicesToBeWrapped[] = { 0, 1 };
    constexpr static int nIndicesToBeWrapped  = 2;
    return new MarmotElementSpatialWrapper( 2, 1, 2, 2, indicesToBeWrapped, nIndicesToBeWrapped, std::move( uelT2D2 ) );
  }
  const static bool
    T2D2_isRegistered = MarmotLibrary::MarmotElementFactory::registerElement( "ADT2D2",
                                                                              MarmotLibrary::ElementCode::T2D2,
                                                                              generateT2D2 );
*/
} // namespace Marmot::Elements::Registration
