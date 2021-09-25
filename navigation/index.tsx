import React from 'react';

import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';

import ConnectUI from '../screens/ConnectUI';
import BluetoothList from '../screens/BluetoothList';
import BluetoothRow from '../components/TestEvent';
import HomeScreen from '../screens/HomeScreen';
import InfoScreen from '../screens/InfoScreen';
import SequenceScreen from '../screens/SequenceScreen';

const Stack = createNativeStackNavigator();

export default function Navigation() {
  const MyTheme = {
    colors: {
      primary: '#ABD9FF',
      background: '#ABD9FF',
      card: '#ABD9FF',
      border: "#ABD9FF",
      text: 'black',
    },
  };

  return (
    <NavigationContainer theme={MyTheme}>
      <Stack.Navigator
        initialRouteName="Home"
        screenOptions={{
          headerShown: false,
          gestureEnabled: true
        }}
      >
        <Stack.Screen 
          name="Home" 
          component={ConnectUI} //ConnectUI
        />
        <Stack.Group screenOptions={{ presentation: 'modal', headerShown: true }}>
          <Stack.Screen name='Connect' component={BluetoothList} />
        </Stack.Group>
        <Stack.Screen
          name="Use"
          component={HomeScreen}
        />
        <Stack.Screen name='Information' component={InfoScreen} />
        <Stack.Screen name='Sequences' component={SequenceScreen} />
      </Stack.Navigator>
    </NavigationContainer> 
  )
}

