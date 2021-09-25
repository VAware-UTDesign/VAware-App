import { StatusBar } from 'expo-status-bar';
import * as React from 'react';
import { Platform, StyleSheet } from 'react-native';
import { FlatList } from 'react-native-gesture-handler';
import TestEvent from '../components/TestEvent';

import { Text, View } from '../components/Themed';

export default function BluetoothList() {
  return (
    <View style={styles.container}>
      <TestEvent />
      <TestEvent />
      <TestEvent />
      <TestEvent />
      <TestEvent />
      <StatusBar style={Platform.OS === 'ios' ? 'light' : 'auto'} />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    width: '100%',
  },
  item: {
    backgroundColor: '#f9c2ff',
    padding: 20,
    marginVertical: 8,
    width: 350,
  },
});
