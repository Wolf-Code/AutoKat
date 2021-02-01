import PreferencesContext from 'account/preferences/PreferencesContext'
import PreferencesPage from 'account/preferences/PreferencesPage'
import { RegistrationPage } from 'authentication/registration'
import { SignInPage } from 'authentication/sign-in'
import EnsureSignedIn from 'authentication/sign-in/EnsureSignedIn'
import SignOutPage from 'authentication/sign-in/SignOutPage'
import SiteContainer from 'common/SiteContainer'
import TranslationsContext from 'core/translations/TranslationsContext'
import React from 'react'
import {
    BrowserRouter as Router,
    Route,
    Switch
} from 'react-router-dom'
import { RecoilRoot } from 'recoil'

const App = () => (
    <RecoilRoot>
        <TranslationsContext>
            <PreferencesContext>
                <Router>
                    <EnsureSignedIn />
                    <SiteContainer>
                        <Switch>
                            <Route 
                                path='/signin'
                                component={ SignInPage } 
                            />
                            <Route 
                                path='/signout'
                                component={ SignOutPage } 
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
            </PreferencesContext>
        </TranslationsContext>
    </RecoilRoot>
)

export default App
