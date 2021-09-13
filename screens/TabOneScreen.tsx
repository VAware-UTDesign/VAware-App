import * as React from 'react';
import { Button, StyleSheet } from 'react-native';

import EditScreenInfo from '../components/EditScreenInfo';
import { Text, View } from '../components/Themed';
import { RootTabScreenProps } from '../types';

export default function TabOneScreen({ navigation }: RootTabScreenProps<'TabOne'>) {
  return (
    <View style={styles.container}>
        <Text style={styles.title}>VAWARE</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container :{
    backgroundColor: '#0078DC',
    flex: 1
  },
  title: {
    fontSize: 60,
    textAlign: 'center',
  }
});
