import PreferencesContext from 'account/preferences/PreferencesContext'
import PreferencesPage from 'account/preferences/PreferencesPage'
import AuthenticationContext from 'authentication/AuthenticationContext'
import { RegistrationPage } from 'authentication/registration'
import { SignInPage } from 'authentication/sign-in'
import SiteContainer from 'common/SiteContainer'
import TranslationsContext from 'core/translations/TranslationsContext'
import React from 'react'
import {
    BrowserRouter as Router,
    Route,
    Switch
} from 'react-router-dom'

const App = () => (
    <TranslationsContext>
        <PreferencesContext>
            <AuthenticationContext>
                <Router>
                    <SiteContainer>
                        <Switch>
                            <Route 
                                path='/signin'
                                component={ SignInPage } 
                            />
                            <Route
                                path='/register'
                                component={ RegistrationPage }
                            />
                            <Route 
                                path='/account'
                                component={ PreferencesPage }
                            />
                        </Switch>
                    </SiteContainer>
                </Router>
            </AuthenticationContext>
        </PreferencesContext>
    </TranslationsContext>
)

export default App
