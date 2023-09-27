#include "Marmot/ADDisplacementFiniteElement.h"
#include "Marmot/Marmot.h"
#include "Marmot/MarmotFiniteElement.h"
#include "Marmot/MarmotFiniteElementSpatialWrapper.h"

enum ADDisplacementElementCode {

  /* TAG explanation excluding prefix 1193
   * XXXX
   * ||||___    4: type of element
   * |||____    3: active fields
   * ||_____    2: number of nodes
   * |______    1: number of nodes
   *
   * active fields:   0: displacement,
   *
   * type of element: 1: 1D full integration,
   *                  2: 2D full integration, plane stress
   *                  3: 3D full integration,
   *                  4: 1D red. integration,
   *                  5: 2D red. integration, plane stress
   *                  6: 3D red. integration
   *                  7: 2D full integration, plane strain
   *                  8: 2D red. integration, plane strain
   * */

  // Truss 2D
  ADT2D2 = 1193202,
  // Plane stress 2D
  ADCPS4  = 1193402,
  ADCPS8R = 1193805,

  // Plane Strain 2D
  ADCPE4  = 1193407,
  ADCPE8R = 1193808,

  // Solid
  ADC3D8   = 1193803,
  ADC3D8R  = 1193806,
  ADC3D20  = 11932003,
  ADC3D20R = 11932006
};

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
                     ADDisplacementElementCode::ADCPS4,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 4 >,
                                          FullIntegration,
                                          ADDisplacementFiniteElement< 2, 4 >::PlaneStress >() );

  const static bool ADCPE4_isRegistered = MarmotElementFactory::
    registerElement( "ADCPE4",
                     ADDisplacementElementCode::ADCPE4,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 4 >,
                                          FullIntegration,
                                          ADDisplacementFiniteElement< 2, 4 >::PlaneStrain >() );

  const static bool ADCPS8R_isRegistered = MarmotElementFactory::
    registerElement( "ADCPS8R",
                     ADDisplacementElementCode::ADCPS8R,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 8 >,
                                          ReducedIntegration,
                                          ADDisplacementFiniteElement< 2, 8 >::PlaneStress >() );

  const static bool ADCPE8R_isRegistered = MarmotElementFactory::
    registerElement( "ADCPE8R",
                     ADDisplacementElementCode::ADCPE8R,
                     makeFactoryFunction< ADDisplacementFiniteElement< 2, 8 >,
                                          ReducedIntegration,
                                          ADDisplacementFiniteElement< 2, 8 >::PlaneStrain >() );

  const static bool ADC3D8_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D8", ADDisplacementElementCode::ADC3D8, []( int elementID ) -> MarmotElement* {
      return new ADDisplacementFiniteElement< 3,
                                              8 >( elementID,
                                                   Marmot::FiniteElement::Quadrature::IntegrationTypes::FullIntegration,
                                                   ADDisplacementFiniteElement< 3, 8 >::SectionType::Solid );
    } );

  const static bool ADC3D20_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D20", ADDisplacementElementCode::ADC3D20, []( int elementID ) -> MarmotElement* {
      return new ADDisplacementFiniteElement< 3, 20 >( elementID,
                                                       Marmot::FiniteElement::Quadrature::IntegrationTypes::
                                                         FullIntegration,
                                                       ADDisplacementFiniteElement< 3, 20 >::SectionType::Solid );
    } );

  const static bool ADC3D20R_isRegistered = MarmotLibrary::MarmotElementFactory::
    registerElement( "ADC3D20R", ADDisplacementElementCode::ADC3D20R, []( int elementID ) -> MarmotElement* {
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
                                                                              ADDisplacementElementCode::T2D2,
                                                                              generateT2D2 );
*/
} // namespace Marmot::Elements::Registration
